//
// Created by Theo Fanet on 14/11/2016.
//

#include "Collision.h"



namespace Gnin{
    namespace Physics{

        CollisionDelegate* Collision::_delegate = NULL;

        /**
         * Body collision
         * First Basic Rectangle collision
         * Then Separated axis method to find fixtures colliding
         */
        bool Collision::checkBodyCollision(Body *b1, Body *b2) {
			if (b1->getBodyType() == BODY_STATIC && b2->getBodyType() == BODY_STATIC)
				return false;

            if((b2->getPosition().x - (b2->getSize().w / 2) >= b1->getPosition().x + (b1->getSize().w / 2))
               || (b2->getPosition().x + (b2->getSize().w / 2) <= b1->getPosition().x - (b1->getSize().w / 2))
               || (b2->getPosition().y - (b2->getSize().h / 2) >= b1->getPosition().y + (b1->getSize().h / 2))
               || (b2->getPosition().y + (b2->getSize().h / 2) <= b1->getPosition().y - (b2->getSize().h / 2)))
                return false;
            else{
				// Delegate call for bodies bounding boxs
                if(_delegate)
                    _delegate->basicBodyCollision(b1, b2);

                /**
                 * Collision detected
                 * Check Fixtures
                 */
                Fixture *f1 = b1->getFixtures();
                Fixture *f2 = b2->getFixtures();

                GVector MTD;

                while(f1){
                    GPos offset1 = b1->getPosition() + f1->getPosition();

                    while(f2){
                        GPos offset2 = b2->getPosition() + f2->getPosition();

                        if(intersectFixture(offset1, offset2, f1, f2, MTD)){
                            f1->setColliding(true);
                            f2->setColliding(true);

							// Delegate call for fixtures
                            if(_delegate)
                                _delegate->fixtureBodyCollision(b1, b2, f1, f2, MTD);
                        }
                        f2 = f2->getNext();
                    }
                    f1 = f1->getNext();
                }

                b1->setColliding(true);
                b2->setColliding(true);

                return true;
            }
        }

		/*
		Calculate the min and max interval 
		between axis and fixture
		*/
        void Collision::calculateInterval(GVector axis, GPos offset, Fixture *fixture, float &min, float &max) {
            std::vector<GPoint> pts = fixture->getVertices();

            if(pts.size()){
                float d = axis.dotproduct((GPoint(offset.x, offset.y) + pts.at(0)).asVector());
                min = max = d;
                for(std::vector<GPoint>::iterator it = pts.begin(); it != pts.end(); ++it){
                    d = (GPoint(offset.x, offset.y) + (*it)).dotproduct(axis);
                    if(d < min)
                        min = d;
                    else if(d > max)
                        max = d;
                }
            }
        }

		/*
		Check if axis separate the polygons
		*/
        bool Collision::axisSeparatePolygons(GVector &axis, GPos offset1, GPos offset2, Fixture *f1, Fixture *f2) {
            float mina, maxa;
            float minb, maxb;

            calculateInterval(axis, offset1, f1, mina, maxa);
            calculateInterval(axis, offset2, f2, minb, maxb);

            if(mina > maxb || minb > maxa)
                return true;

            float d0 = maxa - minb;
            float d1 = maxb - mina;
            float depth = (d0 < d1) ? d0 : d1;

            float axisLengthSquared = axis.dotproduct(axis);

            axis *= depth / axisLengthSquared;

            return false;
        }

		/*
		Determine the MTD vector of the collision
		Wich is the min vector body 2 need to be pushed away
		From body 1
		*/
        GVector Collision::findMTD(std::vector<GVector> pushVectors) {
            GVector MTD = pushVectors.at(0);
            float mind2 = pushVectors.at(0).dotproduct(pushVectors.at(0));

            for(std::vector<GVector>::iterator it = pushVectors.begin() + 1; it != pushVectors.end(); ++it){
                float d2 = (*it).dotproduct((*it));
                if(d2 < mind2){
                    mind2 = d2;
                    MTD = (*it);
                }
            }

            return MTD;
        }

		/*
		Check if fixtures collides 
		and set the MTD vector of collision
		*/
        bool Collision::intersectFixture(GPos offset1, GPos offset2, Fixture *f1, Fixture *f2, GVector &MTD) {
            std::vector<GVector> axis;

            std::vector<GPoint> aPts = f1->getVertices();
            std::vector<GPoint> bPts = f2->getVertices();

			/*
			Axis vs Fixture 1
			*/
            for(size_t j = aPts.size() - 1, i = 0; i < aPts.size(); j = i, i++){
                GPoint  e = (GPoint(offset1.x, offset1.y) + aPts.at(i)) - (GPoint(offset1.x, offset1.y) + aPts.at(j));
                GVector n = GVector(-e.y, e.x);
                if(axisSeparatePolygons(n, offset1, offset2, f1, f2))
                    return false;
                axis.push_back(n);
            }

			/*
			Axis vs Fixture 2
			*/
            for(size_t j = bPts.size() - 1, i = 0; i < bPts.size(); j = i, i++){
                GPoint  e = (GPoint(offset2.x, offset2.y) + bPts.at(i)) - (GPoint(offset2.x, offset2.y) + bPts.at(j));
                GVector n = GVector(-e.y, e.x);
                if(axisSeparatePolygons(n, offset1, offset2, f1, f2))
                    return false;
                axis.push_back(n);
            }

			// Determine MTD
            MTD = findMTD(axis);
            GVector d = ((offset1 + f1->getPosition()) - (offset2 + f2->getPosition())).asVector();

			// Secure MTD B pushed from A
            if(d.dotproduct(MTD) < 0.0f)
                MTD = GVector(-MTD.x, -MTD.y);

            return true;
        }


    }
}