#include "ast.hpp"

#include <iostream>
#include <cstdlib>

Module *TheModule;
FunctionPassManager *TheFPM;
LLVMContext TheContext;
IRBuilder<> Builder(TheContext);

map<string, AllocaInst*> namedValues;

extern Function *MainFja;
extern StructType *VektorTip;
extern Function *PrintfFja;
extern Value *Str;

extern vector<string> dekl_real;
extern vector<string> dekl_int;

Blok::~Blok() {
  for(unsigned i = 0; i < _v.size(); i++)
		delete _v[i];
}

Value* Blok::codegen() const {
	for (unsigned long i = 0; i < _v.size() ; i++)
    _v[i]->codegen();
	
	//return NULL;
	return ConstantInt::get(TheContext, APInt(32, 0));
}

IspisIzraza::~IspisIzraza() {
	delete _i;
}

Value* IspisIzraza::codegen() const {
	Value* broj = _i->codegen();
	
	/* ispis vektora pozivom printf fje */
  vector<Value *> ArgsV;
  ArgsV.push_back(Str);
  ArgsV.push_back(broj);

	return Builder.CreateCall(PrintfFja, ArgsV, "printfCall");
}

Dodjela::~Dodjela() {
	delete _i;
}

Value* Dodjela::codegen() const {
	// treba da provjerimo da li je promjenljiva deklarisana na pocetku
	int ind;
	ind = 0;
	for(unsigned long i = 0; i < dekl_real.size(); i++){
		if(dekl_real[i] == _l){
			ind = 1;
		}
	}
	
	// indikator kojim saznajemo da li je promjenljiva deklarisana u zaglavlju programa
	if(ind == 0){
		cout << "nedefinisana promjenljiva: " << _l << endl;
		exit(EXIT_FAILURE);
	}
	
	Function *fja = Builder.GetInsertBlock()->getParent();
	
	Value *tmp = _i->codegen();
  // Ako promjenljiva nije alocirana, alociramo je
  if (!namedValues.count(_l))
    namedValues[_l] = createEntryBlockAlloca(fja, _l);
  AllocaInst* alloca = namedValues[_l];
  // store instrukcija
  Builder.CreateStore(tmp, alloca);
	
	//return NULL;
	return ConstantInt::get(TheContext, APInt(32, 0));
}

IfThen::~IfThen () {
	delete _i;
	delete _n;
}

Value* IfThen::codegen() const {
	Value* condV = _i->codegen();
  if (!condV)
    return NULL;
	
	// moramo kastovati u i1 tip jer br radi sa njim
	Value* Tmp = Builder.CreateFCmpONE(condV, ConstantFP::get(TheContext, APFloat(0.0)), "ifcond");
  
  Function* theFunction = Builder.GetInsertBlock()->getParent();

  BasicBlock *thenBB = BasicBlock::Create(TheContext, "then", theFunction);
  BasicBlock *mergeBB = BasicBlock::Create(TheContext, "ifcont");

  Builder.CreateCondBr(Tmp, thenBB, mergeBB);
	
  Builder.SetInsertPoint(thenBB);
	
	// zbog ovoga sve naredbe vracaju nesto sto nije NULL
	Value* thenV = _n->codegen();
  if (thenV == NULL){
		cout << "neuspjeh" << endl;
    return NULL;
	}
	
  Builder.CreateBr(mergeBB);
  thenBB = Builder.GetInsertBlock();

  theFunction->getBasicBlockList().push_back(mergeBB);
  Builder.SetInsertPoint(mergeBB);
  
	//return NULL;
	return ConstantInt::get(TheContext, APInt(32, 0));
}

IfThenElse::~IfThenElse () {
	delete _i;
	delete _n1;
	delete _n2;
}

Value* IfThenElse::codegen() const {
	Value* condV = _i->codegen();
  if (!condV)
    return NULL;
	
	// moramo kastovati u i1 tip jer br radi sa njim
	Value* Tmp1 = Builder.CreateFCmpONE(condV, ConstantFP::get(TheContext, APFloat(0.0)), "ifcond");
  
  Function* theFunction = Builder.GetInsertBlock()->getParent();

  BasicBlock *thenBB = BasicBlock::Create(TheContext, "then", theFunction);
  BasicBlock *elseBB = BasicBlock::Create(TheContext, "else");
  BasicBlock *mergeBB = BasicBlock::Create(TheContext, "ifcont");

  Builder.CreateCondBr(Tmp1, thenBB, elseBB);

  Builder.SetInsertPoint(thenBB);
  Value* thenV = _n1->codegen();
  if (!thenV)
    return NULL;
  Builder.CreateBr(mergeBB);
  thenBB = Builder.GetInsertBlock();

  theFunction->getBasicBlockList().push_back(elseBB);
  Builder.SetInsertPoint(elseBB);
  Value* elseV = _n2->codegen();
  if (!elseV)
    return NULL;
  Builder.CreateBr(mergeBB);
  elseBB = Builder.GetInsertBlock();

  theFunction->getBasicBlockList().push_back(mergeBB);
  Builder.SetInsertPoint(mergeBB);
	
	/*
	PHINode *PHI;
	PHI = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");
  PHI->addIncoming(thenV, thenBB);
  PHI->addIncoming(elseV, elseBB);
	
  return PHI;
	*/
	return ConstantInt::get(TheContext, APInt(32, 0));
}

WhileDo::~WhileDo() {
	delete _i;
	delete _n;
}

Value* WhileDo::codegen() const {
	
	Function* theFunction = Builder.GetInsertBlock()->getParent();

  BasicBlock *loopBB = BasicBlock::Create(TheContext, "loop", theFunction);
	
  Builder.CreateBr(loopBB);

  Builder.SetInsertPoint(loopBB);

  
  Value* stopV = _i->codegen();
  if (!stopV)
    return NULL;
	
	// moramo kastovati u i1 tip jer br radi sa njim
	Value* Tmp1 = Builder.CreateFCmpONE(stopV, ConstantFP::get(TheContext, APFloat(0.0)), "loopcond");

  BasicBlock *loopBB1 = BasicBlock::Create(TheContext, "loop1", theFunction);
  BasicBlock *afterLoopBB = BasicBlock::Create(TheContext, "afterloop", theFunction);
  Builder.CreateCondBr(Tmp1, loopBB1, afterLoopBB);

  Builder.SetInsertPoint(loopBB1);  
  if (!_n->codegen())
    return NULL;

  Builder.CreateBr(loopBB);
  
  Builder.SetInsertPoint(afterLoopBB);

	return ConstantInt::get(TheContext, APInt(32, 0));
}

AllocaInst* createEntryBlockAlloca(Function* theFunction, const string& name) {
	// pravimo privremeni Builder koji pise na pocetku trenutne fje
  IRBuilder<> b(&theFunction->getEntryBlock(), theFunction->getEntryBlock().begin());
  return b.CreateAlloca(Type::getDoubleTy(TheContext), 0, name.c_str());
}

void InitializeModuleAndPassManager() {
  TheModule = new Module("Moj modul", TheContext);
  TheFPM = new FunctionPassManager(TheModule);

  // Do simple "peephole" optimizations and bit-twiddling optzns.
  TheFPM->add(createInstructionCombiningPass());
  // Reassociate expressions.
  TheFPM->add(createReassociatePass());
  // Eliminate Common SubExpressions.
  TheFPM->add(createGVNPass());
  // Simplify the control flow graph (deleting unreachable blocks, etc).
  TheFPM->add(createCFGSimplificationPass());
  // Smanjuje broj load/store instrukcija
  TheFPM->add(createPromoteMemoryToRegisterPass());

  TheFPM->doInitialization();
}