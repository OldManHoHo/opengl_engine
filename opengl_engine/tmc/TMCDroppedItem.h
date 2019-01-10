
#include "TGLActor.h"
#include "TGLMaterial.h"
#include "TGLMesh.h"
#include "TGLMeshVertices.h"
#include "useful_structures.h"

class TMCDroppedItem :
	public TGLActor
{
public:
	TGLItemId item_type;

	TMCDroppedItem(TGLItemId in_item_type);
	~TMCDroppedItem();
};
