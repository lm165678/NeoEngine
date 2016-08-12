#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Singleton.h"
#include <SimpleSignal.h>

namespace Neo
{

	//�����¼����ȼ�,�ɸߵ���
	enum eInputEventPriority
	{
		eInputEventPriority_GUI			=	0,		//GUI�¼���Ӧ
		eInputEventPriority_Targeting	=	1,		//���ѡ��Ŀ��
		eInputEventPriority_default		=	2,
		eInputEventPriority_Count
	};

	enum eInputEvent
	{
		eInputEvent_MouseMove,
		eInputEvent_MouseBtnDown,
		eInputEvent_MouseBtnUp,
		eInputEvent_KeyDown,
		eInputEvent_KeyUp,
		eInputEvent_Count
	};

	/*------------------------------------------------
					����������������
	-------------------------------------------------*/

	class CInputManager : public Common::CSingleton<CInputManager>, public OIS::MouseListener, public OIS::KeyListener
	{
		DECLEAR_SINGLETON(CInputManager);
		CInputManager();
		~CInputManager();

		typedef std::function<bool(const OIS::MouseEvent&)> MouseMoveHandler;
		typedef std::function<bool(const OIS::MouseEvent&, OIS::MouseButtonID)> MouseBtnHandler;
		typedef std::function<bool(const OIS::KeyEvent&)> KeyHandler;

	public:
		bool Init();
		void Shutdown();
		bool IsInit() { return m_bIsInit; }
		//���������豸
		void Capture();
		OIS::Mouse*	GetMouse()	{ return mMouse; }

		Common::Signal<bool(const OIS::MouseEvent&)> m_MouseMoveSignal;
		Common::Signal<bool(const OIS::MouseEvent&, OIS::MouseButtonID)> m_MousePressedSignal;
		Common::Signal<bool(const OIS::MouseEvent&, OIS::MouseButtonID)> m_MouseReleasedSignal;
		Common::Signal<bool(const OIS::KeyEvent&)> m_KeyPressedSignal;
		Common::Signal<bool(const OIS::KeyEvent&)> m_KeyReleasedSignal;

	private:
		OIS::InputManager* mInputManager;
		OIS::Mouse*    mMouse;
		OIS::Keyboard* mKeyboard;
		bool			m_bIsInit;

		// OIS::MouseListener
		virtual bool mouseMoved( const OIS::MouseEvent &arg ) { return m_MouseMoveSignal.emit(arg); }
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) { return m_MousePressedSignal.emit(arg, id); }
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) { return m_MouseReleasedSignal.emit(arg, id); }
		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent &arg) { return m_KeyPressedSignal.emit(arg); }
		virtual bool keyReleased(const OIS::KeyEvent &arg) { return m_KeyReleasedSignal.emit(arg); }
	};

}


#endif
