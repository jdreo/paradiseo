/*
  <moFitnessStat.h>
  Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

  Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

  This software is governed by the CeCILL license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.
  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ParadisEO WebSite : http://paradiseo.gforge.inria.fr
  Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef moFitnessStat_h
#define moFitnessStat_h

#include <continuator/moStat.h>

/**
 * The actual class that will be used as base for all statistics
 * that need to be calculated over the solution
 * It is a moStatBase AND an eoValueParam so it can be used in Monitors.
*/
template <class EOT, class T=typename EOT::Fitness>
class moFitnessStat : public moStat<EOT, T>
{
public :
    typedef T Fitness;
    using moStat< EOT, Fitness >::value;

    /**
     * Default Constructor
     * @param _description a description of the stat
     */
    moFitnessStat(std::string _description = "fitness"):
    	moStat<EOT, Fitness>(Fitness(), _description){}

    /**
     * store fitness value
     * @param _sol the corresponding solution
     */
    virtual void operator()(EOT & _sol)
    {
      value() = _sol.fitness();
    }

    /**
     * @return the name of the class
     */
    virtual std::string className(void) const { return "moFitnessStat"; }
};

#endif