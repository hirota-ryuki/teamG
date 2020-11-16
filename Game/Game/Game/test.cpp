#include "stdafx.h"
#include "test.h"

test::test()
{

}

test::~test()
{
}

bool test::Start()
{
	m_player = NewGO<Player>(GOPrio_Defalut);
	return true;
}

void test::Update()
{

}