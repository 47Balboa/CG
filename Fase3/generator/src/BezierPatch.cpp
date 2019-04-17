#include "headers/BezierPatch.h"

BezierPatch::BezierPatch(){}

BezierPatch::BezierPatch(vector<Point*> v) {
	pontosControlo = v;
}

vector<Point*> BezierPatch::getPontosControlo() {
	return getPontosControlo;
}

void BezierPatch::setPontosControlo(vector<Point*> v) {
	pontosControlo = v;
}

void BezierPatch::addPonto(Point* v) {
	pontosControlo.push_back(v);
}
