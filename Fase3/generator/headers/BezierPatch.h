#ifndef __BEZIERPATCH_H__
#define __BEZIERPATCH_H__

#include <vector>
#include "../../src/headers/Point.h"

using namespace std;

class BezierPatch {

	vector<Point*> pontosControlo;

	public:
		BezierPatch();
		BezierPatch(vector<Point*>);
		vector<Point*> getPontosControlo();
		void setPontosControlo(vector<Point*>);
		void addPonto(Point*);
};

#endif