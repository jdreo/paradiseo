/*
* <moeoSharingDiversityAssignment.h>
* Copyright (C) DOLPHIN Project-Team, INRIA Futurs, 2006-2007
* (C) OPAC Team, LIFL, 2002-2007
*
* Arnaud Liefooghe
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

#ifndef MOEOSHARINGDIVERSITYASSIGNMENT_H_
#define MOEOSHARINGDIVERSITYASSIGNMENT_H_

#include <eoPop.h>
#include <comparator/moeoDiversityThenFitnessComparator.h>
#include <distance/moeoDistance.h>
#include <distance/moeoDistanceMatrix.h>
#include <distance/moeoEuclideanDistance.h>
#include <diversity/moeoDiversityAssignment.h>

/**
 * Sharing assignment scheme originally porposed by:
 * D. E. Goldberg, "Genetic Algorithms in Search, Optimization and Machine Learning", Addision-Wesley, MA, USA (1989).
 */
template < class MOEOT >
class moeoSharingDiversityAssignment : public moeoDiversityAssignment < MOEOT >
  {
  public:

    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;


    /**
     * Ctor
     * @param _distance the distance used to compute the neighborhood of solutions (can be related to the decision space or the objective space)
     * @param _nicheSize neighborhood size in terms of radius distance (closely related to the way the distances are computed)
     * @param _alpha parameter used to regulate the shape of the sharing function
     */
    moeoSharingDiversityAssignment(moeoDistance<MOEOT,double> & _distance, double _nicheSize = 0.5, double _alpha = 1.0) : distance(_distance), nicheSize(_nicheSize), alpha(_alpha)
    {}


    /**
     * Ctor with an euclidean distance (with normalized objective values) in the objective space is used as default
     * @param _nicheSize neighborhood size in terms of radius distance (closely related to the way the distances are computed)
     * @param _alpha parameter used to regulate the shape of the sharing function
     */
    moeoSharingDiversityAssignment(double _nicheSize = 0.5, double _alpha = 1.0) : distance(defaultDistance), nicheSize(_nicheSize), alpha(_alpha)
    {}


    /**
     * Sets diversity values for every solution contained in the population _pop
     * @param _pop the population
     */
    void operator()(eoPop < MOEOT > & _pop)
    {
      // 1 - set simuilarities
      setSimilarities(_pop);
      // 2 - a higher diversity is better, so the values need to be inverted
      moeoDiversityThenFitnessComparator < MOEOT > divComparator;
      double max = std::max_element(_pop.begin(), _pop.end(), divComparator)->diversity();
      for (unsigned int i=0 ; i<_pop.size() ; i++)
        {
          _pop[i].diversity(max - _pop[i].diversity());
        }
    }


    /**
     * @warning NOT IMPLEMENTED, DO NOTHING !
     * Updates the diversity values of the whole population _pop by taking the deletion of the objective vector _objVec into account.
     * @param _pop the population
     * @param _objVec the objective vector
     * @warning NOT IMPLEMENTED, DO NOTHING !
     */
    void updateByDeleting(eoPop < MOEOT > & /*_pop*/, ObjectiveVector & /*_objVec*/)
    {
      std::cout << "WARNING : updateByDeleting not implemented in moeoSharingDiversityAssignment" << std::endl;
    }


  protected:

    /** the distance used to compute the neighborhood of solutions */
    moeoDistance < MOEOT , double > & distance;
    /** euclidean distancein the objective space (can be used as default) */
    moeoEuclideanDistance < MOEOT > defaultDistance;
    /** neighborhood size in terms of radius distance */
    double nicheSize;
    /** parameter used to regulate the shape of the sharing function */
    double alpha;


    /**
     * Sets similarities for every solution contained in the population _pop
     * @param _pop the population
     */
    virtual void setSimilarities(eoPop < MOEOT > & _pop)
    {
      // compute distances between every individuals
      moeoDistanceMatrix < MOEOT , double > dMatrix (_pop.size(), distance);
      dMatrix(_pop);
      // compute similarities
      double sum;
      for (unsigned int i=0; i<_pop.size(); i++)
        {
          sum = 0.0;
          for (unsigned int j=0; j<_pop.size(); j++)
            {
              sum += sh(dMatrix[i][j]);
            }
          _pop[i].diversity(sum);
        }
    }


    /**
     * Sharing function
     * @param _dist the distance value
     */
    double sh(double _dist)
    {
      double result;
      if (_dist < nicheSize)
        {
          result = 1.0 - pow(_dist / nicheSize, alpha);
        }
      else
        {
          result = 0.0;
        }
      return result;
    }

  };


#endif /*MOEOSHARINGDIVERSITYASSIGNMENT_H_*/
