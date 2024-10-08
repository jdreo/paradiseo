/*
* <t-moeoChebyshevMetric.cpp>
* Copyright (C) DOLPHIN Project-Team, INRIA Lille-Nord Europe, 2006-2008
* (C) OPAC Team, LIFL, 2002-2008
*
* Arnaud Liefooghe
* Jeremie Humeau
* Francois Legillon
*
* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*
* ParadisEO WebSite : http://paradiseo.gforge.inria.fr
* Contact: paradiseo-help@lists.gforge.inria.fr
*
*/
//-----------------------------------------------------------------------------
// t-moeoAggregationFitnessAssignment.cpp
//-----------------------------------------------------------------------------

#include <eo>
#include <moeo>
#include <cassert>

//-----------------------------------------------------------------------------

class ObjectiveVectorTraits : public moeoObjectiveVectorTraits
{
public:
    static bool minimizing (int /*i*/)
    {
        return true;
    }
    static bool maximizing (int /*i*/)
    {
        return false;
    }
    static unsigned int nObjectives ()
    {
        return 2;
    }
};

typedef moeoRealObjectiveVector < ObjectiveVectorTraits > ObjectiveVector;

typedef MOEO < ObjectiveVector, double, double > Solution;

class DummyEval: public eoEvalFunc<Solution>{
	void operator()(Solution &/*moeo*/){
	}
} eval;
//-----------------------------------------------------------------------------

int main()
{
    std::cout << "[moeoChebyshevMetric] => ";

    // objective vectors
    ObjectiveVector obj0, obj1, obj2, obj3, obj4, obj5, obj6;
    obj0[0] = 3;
    obj0[1] = 3;

    obj1[0] = 2;
    obj1[1] = 2;

    obj2[0] = 1;
    obj2[1] = 1;

    obj4[0] = 0;
    obj4[1] = 0;

    
    std::vector<double> poids;
    poids.resize(2);
    
    poids[0]=2;
    poids[1]=3;
    ObjectiveVector obj_poids(poids);


    // population
    eoPop < Solution > pop;
    pop.resize(3);
    pop[0].objectiveVector(obj0); 
    pop[1].objectiveVector(obj1);
    pop[2].objectiveVector(obj2);
    Solution reference;
    reference.objectiveVector(obj4);
    unsigned int rho=2;

    moeoObjectiveVectorNormalizer<Solution> normalizer(pop,10);

    moeoAugmentedAchievementScalarizingFunctionMetricFitnessAssignment<Solution> fitness(rho,obj4,obj_poids,normalizer,eval);
    moeoAugmentedAchievementScalarizingFunctionMetricFitnessAssignment<Solution> fitness1(rho,obj4,obj_poids);
    moeoAugmentedAchievementScalarizingFunctionMetricFitnessAssignment<Solution> fitness2(rho,obj4,obj_poids,normalizer);
    moeoAugmentedAchievementScalarizingFunctionMetricFitnessAssignment<Solution> fitness3(rho,obj4,obj_poids,eval);
    fitness(pop);
    fitness(reference);
    
    assert(pop[0].fitness()<pop[1].fitness());
    assert(pop[1].fitness()<pop[2].fitness());
 
    std::cout << "Ok" << std::endl;
    
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
