#ifndef PHYSICS_WRAPPER_UTILITIES
#define PHYSICS_WRAPPER_UTILITIES

#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

//#define TINYOBJLOADER_IMPLEMENTATION
#include "../TinyOBJLoader/tiny_obj_loader.h"

#include <math.h>
#include <vector>
#include <string>
#include <iostream>

class PhysicsUtilities
{
public:
	/*
	 * Construct a rigid body from some passed parameters - avoids reused code when setting up different physics objects
	 */
	static btRigidBody* constructRigidBody(btCollisionShape* cShape, btMotionState* mState, bool dynamic, float mass)
	{
		btRigidBody* rBody;
		if (dynamic)
		{
			btVector3 fallInertia(0, 0, 0);
			cShape->calculateLocalInertia(mass, fallInertia);
			btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, mState, cShape, fallInertia);

			rBody = new btRigidBody(fallRigidBodyCI);
		}
		else
		{
			//This is the construction info for a non-dynamic object: moves under NO circumstance
			btRigidBody::btRigidBodyConstructionInfo cInfo(0, mState, cShape, btVector3(0, 0, 0));

			rBody = new btRigidBody(cInfo);
		}
		return rBody;
	}

	/*
	 * Read the vertices of an OBJ file into an vector of vertex positions
	 * Each vertex takes up 3 entries: x, y, z
	 */
	static std::vector<float> readOBJIntoVector(std::string filename)
	{
		/* TinyOBJ setup*/
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials; //Not used

		std::string err;
		bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());

		//bool success = false;

		//Print any errors raised by the OBJ loader
		if (!err.empty())
		{
			std::cerr << err << std::endl;
		}

		//Exit application if could not load OBJ
		if (!success)
		{
			exit(1);
		}

		std::vector<float> OBJVertices;

		//Shapes
		for (size_t shape = 0; shape < shapes.size(); shape++)
		{
			//Polygon faces within a given shape
			size_t index_offset = 0;
			for (size_t face = 0; face < shapes[shape].mesh.num_face_vertices.size(); face++)
			{
				//Imported as triangles, so I -think- this should always be 3...
				//Documentation could be better
				int faceVertCount = shapes[shape].mesh.num_face_vertices[face];

				//Vertices in given face
				for (size_t vert = 0; vert < faceVertCount; vert++)
				{
					tinyobj::index_t i = shapes[shape].mesh.indices[index_offset + vert];
					float vx = attrib.vertices[3 * i.vertex_index + 0];
					float vy = attrib.vertices[3 * i.vertex_index + 1];
					float vz = attrib.vertices[3 * i.vertex_index + 2];
					OBJVertices.push_back(vx);
					OBJVertices.push_back(vy);
					OBJVertices.push_back(vz);
				}
				index_offset += faceVertCount;
			}
		}

		return OBJVertices;
	}
};

#endif
