//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_COLLISION_H
#define GLTEST_COLLISION_H

#include "Body.h"


namespace Gnin{
    namespace Physics{
		/*
		Delegate class for collisions
		*/
        class CollisionDelegate{
        public:
            virtual void basicBodyCollision(Body *b1, Body *b2){}
            virtual void fixtureBodyCollision(Body *b1, Body *b2, Fixture *f1, Fixture *f2, GVector MTD){}
        };

		/*
		Main collisions class
		*/
        class Collision {
        public:
			/*
			Check if two body collides
			And the perform a deeper check with bodies fixtures
			*/
			static bool checkBodyCollision(Body *b1, Body *b2);

			// Delegate setter (static)
            inline static void setDelegate(CollisionDelegate *delegate){ _delegate = delegate; }

        private:
			// Delegate
            static CollisionDelegate *_delegate;

            /**
             * Separated Axis Method
             */
            static void calculateInterval(GVector axis, GPos offset, Fixture *fixture, float &min, float &max);
            static bool axisSeparatePolygons(GVector &axis, GPos offset1, GPos offset2, Fixture *f1, Fixture *f2);
            static bool intersectFixture(GPos offset1, GPos offset2, Fixture *f1, Fixture *f2, GVector &MTD);
            static GVector findMTD(std::vector<GVector> pushVectors);
        };

    }
}


#endif //GLTEST_COLLISION_H
