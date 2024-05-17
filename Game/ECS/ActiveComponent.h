#include "Components.h"
#include "ECS.h"

class ActvieComponent : public Component{
public: 

	void isAcitve() { return active; }

	void destroy() { active = false; }

private:

	bool active = true;

};