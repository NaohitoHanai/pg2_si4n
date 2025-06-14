#include "DataCarrier.h"
#include <assert.h>

DataCarrier::DataCarrier()
{
    player[0] = true;
    player[1] = true;
}

DataCarrier::~DataCarrier()
{
}

void DataCarrier::SetPlayUser(int id, bool user)
{
    assert(id >= 0 && id < 2);
    player[id] = user;
}

bool DataCarrier::IsPlayUser(int id) const
{
    assert(id >= 0 && id < 2);
    return player[id];
}
