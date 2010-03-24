#ifndef KInvariantMassCut_h
#define KInvariantMassCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KLorentzVector.h"

namespace KappaTools
{
	template <typename T>
	class InvariantMassCut : public BaseCut
	{
		private:
			//FIXME: cut inversion should be done via BaseCut class!
			double cut_inversion;
			std::vector< T * > obj;
			double mass_min;
			double mass_max;
		public:
			InvariantMassCut();
			InvariantMassCut(T * tmpObj);
			
			void inverse(bool invert);
			void setPointer(T * tmpObj);
			void setPointer(T * tmpObj1, T * tmpObj2);
			void addPointer(T * tmpObj);
			void setPointer(std::vector< T * > tmpObj);
						
			void setCut(double mass_min_, double mass_max_);
			void setMinCut(double mass_min_);
			void setMaxCut(double mass_max_);
			
			bool getInternalDecision();
			double getDecisionValue();
	};
	
	template <typename T>
	InvariantMassCut<T>::InvariantMassCut() : BaseCut("inv. mass cut"), cut_inversion(false)
	{
		mass_min=0.;
		mass_max=1e5;
	}
	
	template <typename T>
	InvariantMassCut<T>::InvariantMassCut(T * tmpObj) : BaseCut("inv. mass cut"), cut_inversion(false)
	{
		obj.push_back(tmpObj);
		mass_min=0.;
		mass_max=1e5;
	};

	template <typename T>
	void InvariantMassCut<T>::inverse(bool invert) { cut_inversion = invert; }
	
	template <typename T>
	void InvariantMassCut<T>::setPointer(T * tmpObj) 								{	obj.clear(); obj.push_back(tmpObj);														};
	
	template <typename T>
	void InvariantMassCut<T>::setPointer(T * tmpObj1, T * tmpObj2)		{	obj.clear(); obj.push_back(tmpObj1); obj.push_back(tmpObj2);	};			
	
	template <typename T>
	void InvariantMassCut<T>::addPointer(T * tmpObj) 								{	obj.push_back(tmpObj); 																				};
	
	template <typename T>
	void InvariantMassCut<T>::setPointer(std::vector< T * > tmpObj) 	{	obj.clear(); obj=tmpObj; 																			};	
	
	template <typename T>
	void InvariantMassCut<T>::setCut(double mass_min_, double mass_max_) { mass_min = mass_min_; mass_max = mass_max_; };
	
	template <typename T>
	void InvariantMassCut<T>::setMinCut(double mass_min_) { mass_min = mass_min_; };
	
	template <typename T>
	void InvariantMassCut<T>::setMaxCut(double mass_max_) { mass_max = mass_max_; };
	
	template <typename T>
	bool InvariantMassCut<T>::getInternalDecision()
	{
		if (obj.size()==0)
			return false;
		
		RMLV sum;
		for (typename std::vector< T * >::iterator it = obj.begin(); it!=obj.end(); it++)
			if (*it)
				sum+=(*it)->p4;
		if (cut_inversion)
			return (sum.mass()<mass_min || sum.mass()>mass_max);
		else
			return !(sum.mass()<mass_min || sum.mass()>mass_max);
	};
	
	template <typename T>
	double InvariantMassCut<T>::getDecisionValue()
	{
		RMLV sum;
		for (typename std::vector< T * >::iterator it = obj.begin(); it!=obj.end(); it++)
			sum+=(*it)->p4; 
		return sum.mass(); 
	};	
}
#endif
