// COMP710 GP Framework 2021
#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__
class VertexArray
{
	// Member methods:
public:
	VertexArray(const float* pVertices, unsigned int numVertices,
		const unsigned int* pIndices, unsigned int numIndicies);
	~VertexArray();
	void SetActive();
	unsigned int GetNumVertices() const;
	unsigned int GetNumIndicies() const;
protected:
private:
	VertexArray(const VertexArray& vertexArray);
	VertexArray& operator=(const VertexArray& vertexArray);
	// Member data:
public:
protected:
	unsigned int m_numVertices;
	unsigned int m_numIndices;
	unsigned int m_glVertexBuffer;
	unsigned int m_glIndexBuffer;
	unsigned int m_glVertexArray;
private:
};
#endif // __VERTEXARRAY_H__