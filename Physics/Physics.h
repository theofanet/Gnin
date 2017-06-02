//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_PHYSICS_H
#define GLTEST_PHYSICS_H

#include <cmath>
#include <string>
#include <map>

namespace Gnin{

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

    /**
     * GVector
     */
    struct GVector{
        float x, y;

        GVector(){
            x = 0.0f;
            y = 0.0f;
        }

        GVector(float X, float Y){
            x = X;
            y = Y;
        }

        float normalise(){
            float mag = magnitude();
            x = (mag > 0 ? x / mag : x);
            y = (mag > 0 ? y / mag : y);
            return mag;
        }

        bool isNull(){
            return (x == 0 && y == 0);
        }

        GVector copy(){
            return GVector(x, y);
        }

        float dotproduct(GVector v){
            return (x * v.x) + (y * v.y);
        }

        float magnitude(){
            return (float)sqrt(x * x + y * y);
        }

        float lenght(){
            return magnitude();
        }

        GVector project(GVector v){
            GVector N = copy();
            float dot = dotproduct(v);
            N.normalise();
            GVector result;
            result.x = (dot / (N.x * N.x)) * x;
            result.y = (dot / (N.y * N.y)) * y;
            return result;
        }

        void rotate(float angle){
            float xt = (x * cosf(angle)) - (y * sinf(angle));
            float yt = (y * cosf(angle)) + (x * sinf(angle));
            x = xt;
            y = yt;
        }

        GVector operator*(float scalar) const{
            return GVector(x * scalar, y * scalar);
        }

        GVector operator*(GVector v) const{
            return GVector(x * v.x, y * v.y);
        }

        GVector operator/(GVector v) const{
            return GVector(x / v.x, y / v.y);
        }

        GVector operator/(float v) const{
            return GVector(x / v, y / v);
        }

        GVector operator+(GVector v) const{
            return GVector(x + v.x, y + v.y);
        }

        GVector operator-(GVector v) const{
            return GVector(x - v.x, y - v.y);
        }

        const GVector &operator+=(const GVector &v){
            x += v.x;
            y += v.y;
            return *this;
        }

        const GVector &operator*=(const float v){
            x *= v;
            y *= v;

            return *this;
        }

        bool operator==(GVector v) const{
            return (x == v.x && y == v.y);
        }

        bool operator!=(GVector v) const{
            return (x != v.x || y != v.y);
        }
    };


    /**
     * GPoint
     */
    struct GPoint{
        float x, y;

        GPoint(float X = 0, float Y = 0){
            x = X;
            y = Y;
        }

        GPoint operator-(float e){
            return GPoint(x - e, y - e);
        }

        GPoint operator-(GPoint P){
            return GPoint(x - P.x, y - P.y);
        }

        GPoint operator-(GVector P){
            return GPoint(x - P.x, y - P.y);
        }

        GPoint operator+(GPoint P){
            return GPoint(x + P.x, y + P.y);
        }

        GPoint operator+(GVector P){
            return GPoint(x + P.x, y + P.y);
        }

        GVector asVector(){
            return GVector(x, y);
        }

        float dotproduct(GVector v){
            return (x * v.x) + (y * v.y);
        }

        float dotproduct(GPoint p){
            return (x * p.x) + (y * p.y);
        }

        const GPoint &operator+=(const GVector &v){
            x += v.x;
            y += v.y;

            return *this;
        }


        const GPoint &operator-=(const GVector &v){
            x -= v.x;
            y -= v.y;

            return *this;
        }

        GPoint operator*(int i){
            return GPoint(x * i, y * i);
        }

        bool operator==(GPoint v) const{
            return (x == v.x && y == v.y);
        }

        bool operator!=(GPoint v) const{
            return (x != v.x || y != v.y);
        }
    };


    /**
     * GPos
     */
    struct GPos{
        GPos() : x(0), y(0){ }
        GPos(float x, float y) : x(x), y(y){ }

        GPos operator-(float e){
            return GPos(x - e, y - e);
        }

        GPos neg(){
            return GPos(-x, -y);
        }

        GPos operator-(GPos P){
            return GPos(x - P.x, y - P.y);
        }

        GPos operator-(GVector P){
            return GPos(x - P.x, y - P.y);
        }

        GPos operator+(float e){
            return GPos(x + e, y + e);
        }

        GPos operator+(GPos P){
            return GPos(x + P.x, y + P.y);
        }

        GPos operator+(GVector P){
            return GPos(x + P.x, y + P.y);
        }

		GPos operator*(float i) {
			return GPos(x * i, y * i);
		}

		GPos operator/(float i) {
			return GPos(x / i, y / i);
		}

		bool operator==(GPos v) const {
			return (x == v.x && y == v.y);
		}

		bool operator!=(GPos v) const {
			return (x != v.x || y != v.y);
		}

        GVector asVector(){
            return GVector(x, y);
        }

        float x, y;
    };


    /**
     * GSize
     */
    struct GSize{
        GSize() : w(1), h(1){}
        GSize(float w, float h) : w(w), h(h){}

        GSize operator*(int i){
            return GSize(w * i, h * i);
        }

        float w, h;
    };


	/**
	 * GForce
	 */
	struct GForce {
		GForce(float x = 0.0f, float y = 0.0f) : x(x), y(y) { }
		GForce(GVector v) : x(v.x), y(v.y) { }

		GForce operator+(GForce f) {
			return GForce(x + f.x, y + f.y);
		}

		GForce operator-(GForce f) {
			return GForce(x - f.x, y - f.y);
		}

		GForce operator*(float m) {
			return GForce(x * m, y * m);
		}

		GForce operator/(float d) {
			return GForce(x / d, y / d);
		}

		const GForce operator+=(GForce f) {
			x += f.x;
			y += f.y;

			return *this;
		}

        GVector asVector(){
            return GVector(x, y);
        }

		float x, y;
	};

	typedef std::map <std::string, GForce> GForceList;
}

#endif //GLTEST_PHYSICS_H
