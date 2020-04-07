#pragma once


#include "GameState.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>	
#include <UI\Blink.h>

class TitleState: public GameState
{
	public:
		TitleState();

	public:
		virtual ~TitleState();


	public:
		void Initialize() override;
		void Update(float elapsedTime) override;
		void Render() override;
		void Finalize() override;
		// 使用するパーツを設定する時の点滅設定
		void SelectPartsMode(bool flag);

	private:
		struct ConstBuffer {
			DirectX::SimpleMath::Vector4 time;
		};

	private:
		int m_count;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderTexture;
		ConstBuffer                                      m_constBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>	         m_CBuffer;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>        m_PixelShader;
		std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
		DirectX::SimpleMath::Vector2                     m_pos;
		DirectX::SimpleMath::Vector2                     m_pushPos;
		DirectX::SimpleMath::Vector2                     m_shaderPos;
		
		std::unique_ptr<Blink>                           m_blink;
		bool                                             m_blinkFlag;


};
