//
// Created by Maksim on 08.11.2026.
//

#ifndef OOP_STATUS_STATUS_FACTORY_H_
#define OOP_STATUS_STATUS_FACTORY_H_

#include <memory>

#include "status.h"
#include "status_type.h"

class StatusFactory {
public:
	std::shared_ptr<Status> Create(StatusType type) const;
};

#endif  // OOP_STATUS_STATUS_FACTORY_H_
