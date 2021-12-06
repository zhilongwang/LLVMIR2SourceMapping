#include <set>
#include <string>
#include <vector>
#include <map>

#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include <utility>
#include "llvm/Support/Debug.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
// #include "llvm/Transforms/Utils/LoopSimplify.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;
using std::hex;

//#define MYDEBUG

using namespace std;
using namespace llvm;
set<Loop *> LoopSet; /*Set storing loop and subloop */
namespace {
  struct IR2SourceMapping : public ModulePass {

    static char ID;
    IR2SourceMapping() : ModulePass(ID) {}

    bool runOnModule(Module &M) override;
    
    bool doInitialization(Module &M) override;
  };
}

bool IR2SourceMapping::runOnModule(Module &M)
{
	string filename = M.getSourceFileName();
	
	for (auto &F : M){ 
		string fun_name = F.getName();
		for(auto &BB : F){
		
			BasicBlock::iterator HeaderIP =  BB.getFirstInsertionPt();
			const DILocation * DIL = HeaderIP->getDebugLoc();
			if(DIL){
				unsigned int numLine = DIL->getLine();
				unsigned int numColumn = DIL->getColumn();
				BB.print(errs());
				errs() << "Map to source:" << filename << ":" << fun_name << ":" << numLine << ":" << numColumn << "\n";
			}
			
		}
	}
	return true;
}

bool IR2SourceMapping::doInitialization(Module &M)
{
	return true;
}

char IR2SourceMapping::ID = 0;

// Registration to run by default using clang compiler
static void registerMyPass(const PassManagerBuilder &, legacy::PassManagerBase &PM)
{
  PM.add(new IR2SourceMapping());
}

static RegisterStandardPasses RegisterMyPass1(PassManagerBuilder::EP_ModuleOptimizerEarly, registerMyPass);
static RegisterStandardPasses RegisterMyPass2(PassManagerBuilder::EP_EnabledOnOptLevel0, registerMyPass);
