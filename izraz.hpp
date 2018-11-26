#ifndef __IZRAZ_HPP__ 
#define __IZRAZ_HPP__ 1

#include <iostream>

using namespace std;

#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/FileSystem.h"


using namespace llvm;
using namespace llvm::legacy;

class Izraz {
public:
  virtual ~Izraz() {

  }
  virtual Value* codegen() const = 0;
};

class Konstanta : public Izraz {
public:
  Konstanta(float c)
    :_c(c)
  {}
  Value* codegen() const;
private:
  float _c;
};

class Promjenljiva : public Izraz {
public:
  Promjenljiva(string ime)
    :_ime(ime)
  {}
  Value* codegen() const;
private:
  string _ime;
};

class BinOperator : public Izraz {
public:
  BinOperator(Izraz* l, Izraz* d)
    :_l(l), _d(d)
  {}
  ~BinOperator ();
protected:  
  Izraz* _l;
  Izraz* _d;
private:
	BinOperator(const BinOperator& z);
  BinOperator& operator=(const BinOperator& z);
};

class Zbir : public BinOperator {
public:
  Zbir(Izraz* l, Izraz* d)
    :BinOperator(l, d)
  {}
  Value* codegen() const;
};

class Razlika : public BinOperator {
public:
	Razlika(Izraz* l, Izraz* d)
		: BinOperator(l, d)
		{}
	Value* codegen() const;
};

class Proizvod : public BinOperator {
public:
	Proizvod(Izraz* l, Izraz* d)
		: BinOperator(l, d)
		{}
	Value* codegen() const;
};

class Kolicnik : public BinOperator {
public:
	Kolicnik(Izraz* l, Izraz* d)
		: BinOperator(l, d)
		{}
	Value* codegen() const;
};

class Mod : public BinOperator {
public:
	Mod(Izraz* l, Izraz* d)
		: BinOperator(l, d)
		{}
	Value* codegen() const;
};

class Manje : public BinOperator {
public:
	Manje(Izraz* l, Izraz* d)
		: BinOperator(l, d)
		{}
	Value* codegen() const;
};

class Vece : public BinOperator {
public:
	Vece(Izraz* l, Izraz* d)
		: BinOperator(l, d)
		{}
	Value* codegen() const;
};

#endif