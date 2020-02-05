// ピクセルシェーダーの入力
struct PS_INPUT
{
    float4 DiffuseColor : COLOR0; // ディフューズカラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
    float4 DrawColor : COLOR0; // 描画カラー
};


// C++ 側で設定する定数の定義

// 描画するテクスチャ
sampler DiffuseMapTexture : register(s0);

// 描画カラーに乗算する値
float4 cfMultiplyColor : register(c0);

float4 pos : register(c1);


float SDFCircle2D(float2 xy, float2 center, float r)
{
    return (length(center - xy) - r);
}
float SDFCircle3D(float3 xyz, float3 center, float r)
{
    return (length(center - xyz) - r);
}
float SDFLatticeCircle2D(float2 xy, float divider)
{
    return (length(fmod(xy, divider) - divider / 2) - divider / 3);
}
float SDFLatticeCircle3D(float3 xyz, float divider, float r)
{
    return (length(fmod(xyz, divider) - divider / 2) - r);
}

// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
    PS_OUTPUT PSOutput;
    float4 lTextureColor;

    // テクスチャーの色を取得
    lTextureColor = tex2D(DiffuseMapTexture, PSInput.TextureCoord0);

    // 出力する色はテクスチャの色と C++ で設定した値とディフューズカラーを乗算したもの
    //PSOutput.DrawColor = lTextureColor * cfMultiplyColor * PSInput.DiffuseColor;

    
    //float3 eye = float3(0, 0, 0.5f);
    //float3 tpos = float3(PSInput.TextureCoord0.xy * float2((800.f / 600.f), 1.0f), 0);
    //float3 ray = normalize(tpos - eye);
    //float r = 1.0f; // 球体の半径

	PSOutput.DrawColor = float4(0, 0, 0, 1);
	if (0 > SDFLatticeCircle2D((PSInput.TextureCoord0.xy + pos.xy) * float2((800 / 600), 1.0f), 0.1f))
	{
		PSOutput.DrawColor = float4(-1, -PSInput.TextureCoord0.y / 2, -1, PSInput.TextureCoord0.y);
		//return PSOutput;
	}

	//float3 eye = float3(0, 0, 0.5f);
	//float3 tpos = float3(PSInput.TextureCoord0.xy * float2((800.f / 600.f), 1.0f), 0);
	//float3 ray = normalize(tpos - eye);
	//float r = 1.0f; // 球体の半径

	//for (int i = 0; i < 64; ++i)
	//{
	//	//float len = SDFCircle3D(eye, float3(0, 0, 5), r);
	//	//float len = SDFLatticeCircle3D(abs(eye + pos.xyz), r * 4, r / 2);
	//	//float len = sdHexPrism(abs(eye + pos.xyz), float2(2, 1));
	//	//float len = sdTriPrism(abs(eye + pos.xyz), float2(1, 1));
	//	float len = sdOctahedron(abs(eye + pos.xyz), r);
	//	eye += ray * len;
	//	if (len < 0.001f)
	//	{
	//		//return float4((float)(64- i) / 64.0f, (float)(64-i) / 64.0f, (float)(64-i) / 64.0f, 1);
	//		//PSOutput.DrawColor = float4(PSInput.TextureCoord0.x / r * cfMultiplyColor.x, PSInput.TextureCoord0.y / r * cfMultiplyColor.y,  cfMultiplyColor.z, 1);
	//		PSOutput.DrawColor = float4(PSInput.TextureCoord0.x / r, PSInput.TextureCoord0.y / r, cfMultiplyColor.z, 1);
	//		return PSOutput;
	//	}
	//}
	
	//PSOutput.DrawColor = float4(0, 0, 0, 1);
	PSOutput.DrawColor += float4(1, 1, 1, 0);
    // 関数の戻り値がラスタライザに渡される
    return PSOutput;
}
