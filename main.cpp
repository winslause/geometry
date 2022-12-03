#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Triangle
{
    // Structure to store the indices of the three vertices that make up a triangle
    int v1, v2, v3;
};

struct Edge
{
    // Structure to store the indices of the two vertices that make up an edge
    int v1, v2;
};

int main()
{
    vector<Triangle> triangles; // vector to store the input triangles
    vector<Edge> edges; // vector to store the input edges
    vector<Triangle> newTriangles; // vector to store the output triangles
    vector<Edge> newEdges; // vector to store the output edges
    int vertexCount = 0; // variable to store the number of vertices
    int triangleCount = 0; // variable to store the number of triangles
    int edgeCount = 0; // variable to store the number of edges

    // Open the input file
    ifstream fin("input.txt");

    // Read the number of vertices
    fin >> vertexCount;

    // Read the number of triangles
    fin >> triangleCount;

    // Read the number of edges
    fin >> edgeCount;

    // Read the triangles
    for (int i = 0; i < triangleCount; i++)
    {
        Triangle t;
        fin >> t.v1 >> t.v2 >> t.v3;
        triangles.push_back(t);
    }

    // Read the edges
    for (int i = 0; i < edgeCount; i++)
    {
        Edge e;
        fin >> e.v1 >> e.v2;
        edges.push_back(e);
    }

    // Close the input file
    fin.close();

    // Loop subdivision:
    // For each triangle, create 4 new triangles
    // and add a new vertex in the center of each original edge
    for (int i = 0; i < triangleCount; i++)
    {
        Triangle t = triangles[i];

        // Get the indices of the three edges of the triangle
        int e1 = -1, e2 = -1, e3 = -1;
        for (int j = 0; j < edgeCount; j++)
        {
            Edge e = edges[j];
            if ((e.v1 == t.v1 && e.v2 == t.v2) || (e.v1 == t.v2 && e.v2 == t.v1))
                e1 = j;
            else if ((e.v1 == t.v2 && e.v2 == t.v3) || (e.v1 == t.v3 && e.v2 == t.v2))
                e2 = j;
            else if ((e.v1 == t.v3 && e.v2 == t.v1) || (e.v1 == t.v1 && e.v2 == t.v3))
                e3 = j;
        }

        // Add the new vertex in the center of each edge
        vertexCount++;
        edges[e1].v2 = vertexCount;
        edges[e2].v2 = vertexCount;
        edges[e3].v2 = vertexCount;

        // Create the four new triangles
        Triangle t1, t2, t3, t4;
        t1.v1 = t.v1;
        t1.v2 = edges[e1].v2;
        t1.v3 = edges[e3].v2;
        t2.v1 = t.v2;
        t2.v2 = edges[e1].v2;
        t2.v3 = edges[e2].v2;
        t3.v1 = t.v3;
        t3.v2 = edges[e2].v2;
        t3.v3 = edges[e3].v2;
        t4.v1 = edges[e1].v2;
        t4.v2 = edges[e2].v2;
        t4.v3 = edges[e3].v2;

        // Add the four new triangles to the output
        newTriangles.push_back(t1);
        newTriangles.push_back(t2);
        newTriangles.push_back(t3);
        newTriangles.push_back(t4);
    }

    // Add the new edges to the output
    for (int i = 0; i < edgeCount; i++)
    {
        newEdges.push_back(edges[i]);
    }

    // Open the output file
    ofstream fout("output.txt");

    // Write the number of vertices
    fout << vertexCount << endl;

    // Write the number of triangles
    fout << 4*triangleCount << endl;

    // Write the number of edges
    fout << edgeCount << endl;

    // Write the triangles
    for (int i = 0; i < 4*triangleCount; i++)
    {
        fout << newTriangles[i].v1 << " " << newTriangles[i].v2 << " " << newTriangles[i].v3 << endl;
    }

    // Write the edges
    for (int i = 0; i < edgeCount; i++)
    {
        fout << newEdges[i].v1 << " " << newEdges[i].v2 << endl;
    }

    // Close the output file
    fout.close();

    return 0;
}
