#ifndef _POTENTIAL_
#define _POTENTIAL_
//The goal of this class is to learn a decision tree given a target node and its neighbourhood.
//Learning is done in two phases. In the first phase we perform consider one neighbour variable
//at a time and then split the node which improves the score the most.

#include <queue>
#include <list>
using namespace std;
#include "gsl/gsl_randist.h"
#include "CommonTypes.H"
#include "RegressionTree.H"
class Evidence;
class EvidenceManager;
class Variable;
class Potential
{
	public:
	Potential();
	~Potential();
	typedef enum
	{
		FACTOR,
		MARKOV_BNKT
	}VariableRole;
	int setAssocVariable(Variable*,VariableRole);
	VSET& getAssocVariables();
	int potZeroInit();
	int calculateConditionalEntropy();
	double getConditionalEntropy();
	double getJointEntropy();
	int setEvidenceManager(EvidenceManager*);
	int setMinLeafSize(int);
	int populateMe(double,int);
	int populateMeFromFile(const char*,int);
	int clearMe();
	double getJointPotValueFor(INTINTMAP&);
	double getJointPotValueForConf(string& varConf);
	int generateSample(INTINTMAP& jointConf, int vId,gsl_rng* r);
	double predictSample(map<int,Evidence*>* jointConf, int vId);
	double getMSE(ofstream&);
	double getTestMSE(EvidenceManager* testEvManager, ostream& oFile);
	int dumpPotential(ostream&);
	
	// DC added to print sorted values to tab file
	int dumpExpressionTab(RegressionTree* theTree, int fId, vector<string>* columnNames, ostream& outFile);
	
	// DC added to print sorted values to hmawk file
	int dumpExpressionHmawk(RegressionTree* theTree, int fId, vector<string>* columnNames, ostream& outFile);
	
	// dump tree (trying to get it to work)
	int dumpTreeToNetwork(RegressionTree* currNode, ostream& oFile, const char* targetName, map<int,int> &timesSeen, int sId, vector<string>* columnNames);
	
	// dump node data for Cytoscape
	int dumpNodeInfo(RegressionTree* theTree, int fId, vector<string>* columnNames, ostream& oFile);
	
	int makeValidJPD();
	//RegressionTree* getRegressionTree();
	vector<RegressionTree*>& getForest();
	int showTree();
	int showTree(RegressionTree*);
	int prune();
	int getAssocVariables_PostPruning(INTINTMAP&);
	int generateSamplesForTree_Bootstrap(vector<int>& dataSamples);
	int generateSamplesForTree_Stability(vector<int>& dataSamples);
	private:
	double getMSE(RegressionTree*);
	double computeEntropyIfDeleted(Rule* r,int delMe,int&);
	int reducePruneSet(Rule* r);
	int removeDuplicateCoverage();
	vector<RegressionTree*> dtreeSet;
	EvidenceManager* evMgr;
	map<int,int> done;
	VSET varSet;
	INTINTMAP factorVariables;
	INTINTMAP markovBlnktVariables;
	double conditionalEntropy;
	double jointEntropy;
	vector<Rule*> prunedRuleSet;
	double lambda;
	INTINTMAP pruneDataSet;
	map<int,INTINTMAP*> dataRuleCoverage;
	int minLeafSize;
	gsl_rng* r;
	int gcnt;
};
#endif
