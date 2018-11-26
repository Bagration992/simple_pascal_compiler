#include "izraz.hpp"

extern LLVMContext TheContext;
extern IRBuilder<> Builder;

extern map<string, AllocaInst*> namedValues;

Value* Konstanta::codegen() const {
  return ConstantFP::get(TheContext, APFloat(_c+0.0));
}

Value* Promjenljiva::codegen() const {
	AllocaInst *v = namedValues[_ime];
  if (!v) {
    cerr << "Nepostojeca promenljiva " << _ime << endl;
    return NULL;
  }
  return Builder.CreateLoad(v);
}

BinOperator::~BinOperator() {
	delete _l;
	delete _d;
}

Value* Zbir::codegen() const {
	Value *l = _l->codegen();
  Value *d = _d->codegen();
	
  return Builder.CreateFAdd(l, d, "tmpadd");
}

Value* Razlika::codegen() const {
	Value *l = _l->codegen();
	Value *d = _d->codegen();
	
	return Builder.CreateFSub(l, d, "tmpsub");
}

Value* Proizvod::codegen() const {
	Value *l = _l->codegen();
	Value *d = _d->codegen();
	
	return Builder.CreateFMul(l, d, "tmpmul");
}

Value* Kolicnik::codegen() const {
	Value *l = _l->codegen();
	Value *d = _d->codegen();
	
	return Builder.CreateFDiv(l, d, "tmpdiv");
}

Value* Mod::codegen() const {
	Value *l = _l->codegen();
	Value *d = _d->codegen();
	
	return Builder.CreateFRem(l, d, "tmpmod");
}

Value* Manje::codegen() const {
	Value *l = _l->codegen();
	Value *d = _d->codegen();

	Value* tmp = Builder.CreateFCmpULT(l, d, "tmpless");
	return Builder.CreateUIToFP(tmp, Type::getDoubleTy(TheContext), "tmpbool");
}

Value* Vece::codegen() const {
	Value *l = _l->codegen();
	Value *d = _d->codegen();
	
	Value* tmp = Builder.CreateFCmpUGT(l, d, "tmpgt");
	return Builder.CreateUIToFP(tmp, Type::getDoubleTy(TheContext), "tmpbool");
}