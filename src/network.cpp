#include <vector>
#include <iostream> 
#include <map> 
#include <iterator> 
#include <algorithm> 
#include "network.h"
#include "random.h"
#include "simulation.h"

using namespace std;

 

/*! Resizes the list of nodes (\ref values) */
void Network :: resize(const size_t& s)
{
	map<size_t,size_t>::iterator it;
	values.clear();
	values.resize(s);
	RNG.normal(values,0,1);
	links.clear();
}


/*! Adds a bidirectional link between two nodes
  @param[in] a,b the indexes if the two nodes 
  @param[out] success the link was succesfully inserted
 */
bool Network :: add_link(const size_t& a, const size_t& b)
{
	if(a==b or a>=values.size() or b>=values.size()) return false;
	else
	{
		for(auto I : links)
		{
			if((I.first==a or I.first==b) and (I.second == a or I.second==b))
			{
				return false;
			}
		}
		links.insert(make_pair(a,b));
		links.insert(make_pair(b,a));
		return true;
	}
	return false;
}



/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen) where *degree(n)* is Poisson-distributed.

  All previous links are cleared first.
  @param mean_deg the average of the Poisson distribution.
 */
size_t Network :: random_connect(const double& mean_deg)
{
	links.clear();
	for(int i(0);i<values.size();++i)
	{
		size_t deg;
		deg = RNG.poisson(mean_deg);
		for(int j(0);j<deg;++j)
		{
			while(!add_link(i,RNG.uniform_double(0,values.size())) and ((degree(i)<values.size()-1))) continue;
		}
	}
	return (links.size()/2);
}


/*! Resets all node values.
  @param[in] vector of new node values
  @param[out] number of nodes succesfully reset
 */
size_t Network :: set_values(const std::vector<double>& val)
{
	values.clear();
	values=val;
	return (val.size());
}


/*! Number of nodes */
size_t Network :: size() const
{
	return (values.size());
}


/*! Degree (number of links) of node no *n* */
size_t Network :: degree(const size_t &_n) const
{
	return (links.count(_n));	
}


/*! Value of node no *n* */
double Network :: value(const size_t &_n) const
{
	return (values[_n]);	
}


///*! All node values in descending order */
vector<double> Network :: sorted_values() const
{	
	vector<double> SortedValues(values);
	sort(SortedValues.begin(),SortedValues.end(), greater<double>());
	return SortedValues;
}


/*! All neighbors (linked) nodes of node no *n* */
std::vector<size_t> Network :: neighbors(const size_t& n) const
{
	vector<size_t> neig;
	for (auto i : links)
	{
		if(i.first==n)
		{
			neig.push_back(i.second);
		}
	}
	return neig;
}
