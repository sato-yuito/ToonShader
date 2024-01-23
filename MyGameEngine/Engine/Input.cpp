#include "Input.h"
namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;//�f�o�C�X�I�u�W�F�N�g
	BYTE keyState[256] ;//������Ă��邩�ǂ����̕ϐ���z��ŗp��
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��
	XMVECTOR mousePosition;

	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr; //�G���[�����p
		hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);//�f�o�C�X�I�u�W�F�N�g�̍쐬
		hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);//�f�o�C�X�̎�ނ��w��
		hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//�������x���̐ݒ�
		
		if (FAILED(hr))
		{
			MessageBox(NULL, "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
			
			return hr;
		}
	}

	//�L�[�̏�Ԃ��擾
	void Update()
	{
		memcpy(prevKeyState,keyState,sizeof(keyState));
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//����̃L�[�������ꂽ���ǂ���
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode]&0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode)&&!(prevKeyState[keyCode]&0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����Ă��Ȃ��đO��͉�����
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}
}