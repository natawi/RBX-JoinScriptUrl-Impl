#pragma once

namespace Patches
{
	struct Patch
	{
		void** toHookPointer;
		void* hookFunction;
	};

	extern std::vector<Patch> patchList;

	void Apply();
}

#define START_PATCH_LIST() std::vector<Patches::Patch> Patches::patchList = {
#define ADD_PATCH(a, b) { (void**)&(a), (b) }, 
#define END_PATCH_LIST() };
