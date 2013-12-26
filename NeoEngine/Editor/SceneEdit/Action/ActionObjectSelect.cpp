#include "stdafx.h"
#include "ActionObjectSelect.h"
#include "Manipulator/ManipulatorScene.h"


ActionObjectSelect::ActionObjectSelect()
//:m_driftSelection(nullptr)
{

}

void ActionObjectSelect::Enter()
{
	ManipulatorSystem.GetObject().ClearSelection();
}

void ActionObjectSelect::Leave()
{
// 	if (m_driftSelection)
// 	{
// 		ManipulatorSystem.GetObject().ShowEntityGizmo(m_driftSelection, false, ManipulatorObject::eEditMode_Select);
// 		m_driftSelection = nullptr;
// 	}
}

void ActionObjectSelect::OnMouseLButtonUp( const SActionParam& param )
{
// 	ManipulatorObject& manObject = ManipulatorSystem.GetObject();
// 	const Ray ray = RenderSys.m_pMainCamera->getCameraToViewportRay(param.m_ptRelative.x, param.m_ptRelative.y);
// 	Entity* pCurDriftEnt = dynamic_cast<Entity*>(manObject.DoRaySceneQuery(ray, eQueryMask_Entity));
// 	Entity* pOldSel = manObject.GetSelection();
// 
// 	//ѡ������
// 	if (pCurDriftEnt && pCurDriftEnt != pOldSel)
// 	{
// 		manObject.SetSelection(pCurDriftEnt);
// 		//ȡ����drift״̬
// 		if(m_driftSelection == pCurDriftEnt)
// 			m_driftSelection = nullptr;
// 	}
}

void ActionObjectSelect::OnMouseMove( const SActionParam& param )
{
// 	ManipulatorObject& manObject = ManipulatorSystem.GetObject();
// 	const Ray ray = RenderSys.m_pMainCamera->getCameraToViewportRay(param.m_ptRelative.x, param.m_ptRelative.y);
// 	Entity* pCurDriftEnt = dynamic_cast<Entity*>(manObject.DoRaySceneQuery(ray, eQueryMask_Entity));
// 
// 	if(manObject.GetSelection() && pCurDriftEnt == manObject.GetSelection())
// 		return;
// 
// 	//����drift�����Χ��ָʾ��
// 	if (pCurDriftEnt && m_driftSelection)
// 	{
// 		if(pCurDriftEnt != m_driftSelection)
// 		{		
// 			manObject.ShowEntityGizmo(m_driftSelection, false, ManipulatorObject::eEditMode_Select);
// 			manObject.ShowEntityGizmo(pCurDriftEnt, true, ManipulatorObject::eEditMode_Select, true);
// 			m_driftSelection = pCurDriftEnt;
// 		}
// 	}
// 	else if(m_driftSelection)
// 	{
// 		manObject.ShowEntityGizmo(m_driftSelection, false, ManipulatorObject::eEditMode_Select);
// 		m_driftSelection = nullptr;
// 	}
// 	else if(pCurDriftEnt)
// 	{
// 		manObject.ShowEntityGizmo(pCurDriftEnt, true, ManipulatorObject::eEditMode_Select, true);
// 		m_driftSelection = pCurDriftEnt;
// 	}
}


