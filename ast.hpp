#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

#include "izraz.hpp"

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

class Naredba {
public:
	virtual ~Naredba() {}
	virtual Value* codegen() const = 0;
};

class Blok : public Naredba {
public:
	Blok(vector<Naredba *> v)
    : _v(v)
  {}
  ~Blok();
  Value* codegen() const;
private:
  Blok(const Blok &n);
  Blok& operator=(const Blok &n);
  vector<Naredba*> _v;
};


class IspisIzraza : public Naredba {
public:
	IspisIzraza(Izraz* i)
		: _i(i)
	{}
	~IspisIzraza ();
	Value* codegen() const;
private:
	IspisIzraza(const IspisIzraza& n);
	IspisIzraza& operator=(const IspisIzraza& n);
	Izraz *_i;
};

class Dodjela : public Naredba {
public:
	Dodjela(string l, Izraz *i)
		: _l(l), _i(i)
	{}
	~Dodjela();
	Value* codegen() const;
private:
	Dodjela(const Dodjela& n);
  Dodjela& operator=(const Dodjela& n);
	string _l;
	Izraz* _i;
};

class IfThen : public Naredba {
public:
  IfThen(Izraz* i, Naredba* n)
    : _i(i), _n(n)
  {}
  ~IfThen();
  Value* codegen() const;
private:
  IfThen(const IfThen &n);
  IfThen& operator=(const IfThen &n);
  Izraz* _i;
  Naredba* _n;
};

class IfThenElse : public Naredba {
public:
  IfThenElse(Izraz* i, Naredba* n1, Naredba* n2)
    : _i(i), _n1(n1), _n2(n2)
  {}
  ~IfThenElse();
  Value* codegen() const;
private:
  IfThenElse(const IfThenElse &n);
  IfThenElse& operator=(const IfThenElse &n);
  Izraz* _i;
  Naredba* _n1;
	Naredba* _n2;
};

class WhileDo : public Naredba {
public:
  WhileDo(Izraz* i, Naredba* n)
    : _i(i), _n(n)
  {}
  ~WhileDo();
  Value* codegen() const;
private:
  WhileDo(const WhileDo &n);
  WhileDo& operator=(const WhileDo &n);
  Izraz* _i;
  Naredba* _n;
};

AllocaInst* createEntryBlockAlloca(Function* theFunction, const string& name);
void InitializeModuleAndPassManager();

#endif