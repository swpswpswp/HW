#pragma once
#include "CP_NodeFactory.h"
#include "CP_StudentProduct.h"

class CP_StudentSystem {
	CP_NodeFactory m_factory;
	CP_StudentProduct m_product;
public:
	CP_StudentSystem();
	void mb_run();
};
