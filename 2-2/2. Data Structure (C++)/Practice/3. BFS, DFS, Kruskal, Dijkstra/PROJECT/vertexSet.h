#ifndef _VERTEXSET_H_
#define _VERTEXSET_H_

#include <iostream>

class vertexSet
{
private:
	int* m_Parent;
	int m_Size;

public:
	vertexSet(int size) {//Initialize the constructor
		m_Parent = new int[size];
		//memset(m_Parent, -1, size * sizeof(int) );
		for (int i = 0; i < size; i++)
		{
			m_Parent[i] = -1;
		}
		m_Size = size;
	}
	~vertexSet() { delete[]m_Parent; }

	int Find(int ver)//Find the root of the tree containing element ver
	{
		int r;
		for (r = ver; m_Parent[r] >= 0; r = m_Parent[r]);//find root
		
		while (ver != r) {//collapse
			int s = m_Parent[ver];
			m_Parent[ver] = r;
			ver = s;
		}
		
		return r;
	}

	void Union(int v1, int v2) // Union sets with roots v1,v2
	{
		int temp = m_Parent[Find(v1)] + m_Parent[Find(v2)];
		if (m_Parent[Find(v1)] > m_Parent[Find(v2)]) {//v1 has fewer nodes
			m_Parent[Find(v1)] = Find(v2);
			m_Parent[Find(v2)] = temp;
		}
		else {//v2 has fewer nodes
			m_Parent[Find(v2)] = Find(v1);
			m_Parent[Find(v1)] = temp;
		}
	}
};


#endif

