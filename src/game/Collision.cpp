#include "Collision.h"

/**
 * @brief gets the length of a vector minus an offset of another vector
 * note: all vectors have a length of two
 * 
 * @param vector 
 * @param offset 
 * @return float 
 */
float Collision::getVectorLength(const sf::Vector2f &vector, const sf::Vector2f &offset) {
    return sqrt(pow(vector.x - offset.x, 2) + pow(vector.y - offset.y, 2));
}

/**
 * @brief gets the dot product of two vectors
 * note: all vectors have a length of two
 * 
 * @param vector1 
 * @param vector2 
 * @return float 
 */
float Collision::getDotProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

/**
 * @brief performs the seperating axis theorem collision detection between two sprites
 * 
 * @param rectangle1 
 * @param rectangle2 
 * @return true, if colliding
 * @return false otherwise
 */
bool Collision::isCollidingSAT(const sf::Sprite &rectangle1, const sf::Sprite &rectangle2) {

	sf::Sprite rectangle[2] = {rectangle1, rectangle2}; //the rectangles
	sf::Vector2f rectanglePoints[2][4]; //the bounding box points
	sf::Vector2f rectangleRotatedPoints[2][4]; //the points of the rectangle, when rotated
	sf::Vector2f rectangleNormals[2][4]; //the normals of each rectangle
	sf::Vector2f normals[4]; //the four most important normals
	sf::Vector2f recangleAxisPoints[2][4]; //the starting and ending projection points

    //get the edges of the boxes
	for (int i = 0; i < 2; i++) {
		//get corner points of bounding box
		rectanglePoints[i][0] = rectangle[i].getTransform().transformPoint(sf::Vector2f(0.0f, 0.0f));
		rectanglePoints[i][1] = rectangle[i].getTransform().transformPoint(sf::Vector2f(rectangle[i].getLocalBounds().width, 0.0f));
		rectanglePoints[i][2] = rectangle[i].getTransform().transformPoint(sf::Vector2f(rectangle[i].getLocalBounds().width, rectangle[i].getLocalBounds().height));
		rectanglePoints[i][3] = rectangle[i].getTransform().transformPoint(sf::Vector2f(0.0f, rectangle[i].getLocalBounds().height));

		//get corner points of rotated rectangle
		sf::Vector2f topLeft(rectangle[i].getLocalBounds().left, rectangle[i].getLocalBounds().top);
		rectangleRotatedPoints[i][0] = rectangle[i].getTransform() * topLeft;

		sf::Vector2f topRight(rectangle[i].getLocalBounds().left + rectangle[i].getLocalBounds().width, rectangle[i].getLocalBounds().top);
		rectangleRotatedPoints[i][1] = rectangle[i].getTransform() * topRight;

		sf::Vector2f bottomRight(rectangle[i].getLocalBounds().left + rectangle[i].getLocalBounds().width, rectangle[i].getLocalBounds().top + rectangle[i].getLocalBounds().height);
		rectangleRotatedPoints[i][2] = rectangle[i].getTransform() * bottomRight;

		sf::Vector2f bottomLeft(rectangle[i].getLocalBounds().left, rectangle[i].getLocalBounds().top + rectangle[i].getLocalBounds().height);
		rectangleRotatedPoints[i][3] = rectangle[i].getTransform() * bottomLeft;

		//get normals
		for (int j = 0; j < 4; j++) {
			int k = j + 1;
			k %= 4;

			sf::Vector2f normalPosition = sf::Vector2f(rectangleRotatedPoints[i][k].y - rectangleRotatedPoints[i][j].y, rectangleRotatedPoints[i][k].x - rectangleRotatedPoints[i][j].x);

			if (normalPosition.y != 0) {
				normalPosition.y *= -1;
			}

			float vectorLength = getVectorLength(normalPosition, sf::Vector2f(0.f, 0.f));

			if (vectorLength > 0) {
				vectorLength = 1 / vectorLength;
			}

			normalPosition.x *= vectorLength;
			normalPosition.y *= vectorLength;

			rectangleNormals[i][j] = normalPosition;
		}

	}

    //since a rectangle has duplicated edges, it's enough to just take 2 different normals from both rectangles
	normals[0] = rectangleNormals[0][0];
	normals[1] = rectangleNormals[0][1];
	normals[2] = rectangleNormals[1][2];
	normals[3] = rectangleNormals[1][3];

	//project the edges of a rectangle onto the axis
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {

			float minProjection = getDotProduct(rectanglePoints[i][0], normals[j]);
			float maxProjection = minProjection;

			for (int k = 0; k < 4; k++) {
				float currentProjection = getDotProduct(rectanglePoints[i][k], normals[j]);
				//Is it a max or min projection on the axis?
				if (minProjection > currentProjection)	//For min
					minProjection = currentProjection;
				if (currentProjection > maxProjection)  //For max
					maxProjection = currentProjection;
			}
			recangleAxisPoints[i][j] = sf::Vector2f(maxProjection, minProjection);
		}
	}
	//check if projections on the axis overlap
    for (int i = 0; i < 4; i++) {
        //if the projections don't overlap for even just one axis, then there is no collision
		//note: the distance from x to y is the projection on the axis. the x and y are not different axis
        if ((recangleAxisPoints[0][i].x < recangleAxisPoints[1][i].y || recangleAxisPoints[1][i].x < recangleAxisPoints[0][i].y) == true) {
            return false;
        }
    }
    return true;
}

/**
 * @brief performs axis aligned bounding box collision detection of two sprites
 * 
 * @param rectangle1 
 * @param rectangle2 
 * @return true, if colliding
 * @return false otherwise
 */
bool Collision::isCollidingAABB(const sf::Sprite& rectangle1, const sf::Sprite& rectangle2) {
	return rectangle1.getGlobalBounds().intersects(rectangle2.getGlobalBounds());
}

/**
 * @brief performs axis aligned bounding box collision detection of two sprites
 * 
 * @param rectangle1 
 * @param rectangle2 
 * @return true, if rectangle2's bounding box is fully contained in rectangle1's bounding box
 * @return false otherwise
 */
bool Collision::isFullyCollidingAABB(const sf::Sprite &rectangle1, const sf::Sprite &rectangle2) {
	return (rectangle1.getGlobalBounds().contains(rectangle2.getGlobalBounds().left, rectangle2.getGlobalBounds().top) &&
			rectangle1.getGlobalBounds().contains(rectangle2.getGlobalBounds().left + rectangle2.getGlobalBounds().width, rectangle2.getGlobalBounds().top + rectangle2.getGlobalBounds().height));
}