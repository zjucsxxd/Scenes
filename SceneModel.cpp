/*
* Copyright (c) 2009, 2010, 2011, 2012 Brendon J. Brewer.
*
* This file is part of DNest3.
*
* DNest3 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DNest3 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with DNest3. If not, see <http://www.gnu.org/licenses/>.
*/

#include "SceneModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>
#include <iomanip>

using namespace std;
using namespace DNest3;

SceneModel::SceneModel()
:pixels(256, vector<double>(256))
{

}

void SceneModel::fromPrior()
{
	for(size_t i=0; i<pixels.size(); i++)
		for(size_t j=0; j<pixels[i].size(); j++)
			pixels[i][j] = -log(randomU());
}

double SceneModel::perturb()
{
	double logH = 0.;

	double chance = pow(10., 0.5 - 4.*randomU());
	double scale = pow(10., 1.5 - 6.*randomU());
	double U;

	for(size_t i=0; i<pixels.size(); i++)
	{
		for(size_t j=0; j<pixels[i].size(); j++)
		{
			if(randomU() <= chance)
			{
				U = 1. - exp(-pixels[i][j]);
				U += scale*randn();
				U = mod(U, 1.);
				pixels[i][j] = -log(1. - U);
			}
		}
	}

	return logH;
}

double SceneModel::logLikelihood() const
{
	return 0.;
}

void SceneModel::print(ostream& out) const
{
	out<<setprecision(4);
	for(size_t i=0; i<pixels.size(); i++)
		for(size_t j=0; j<pixels[i].size(); j++)
			out<<pixels[i][j]<<' ';
}

string SceneModel::description() const
{
	return string("A million pixels.");
}
