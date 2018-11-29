
#include "TGLActor.h"
#include "TGLMeshVertices.h"
#include "useful_structures.h"
#include "TGLMesh.h"
#include "TGLMaterial.h"

class TMCDroppedItem :
	public TGLActor
{
public:
	TGLItemId item_type;

	TMCDroppedItem(TGLItemId in_item_type);
	~TMCDroppedItem();
};
