//======================================================
// File Name	: NeuralNetwork.h
// Summary		: ニューラルネットワーク
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


class NeuralNetworkLayer
{
public:
	//入力層ノード数
	int			        m_numNodes;
	//隠れ層ノード数
	int			        m_numChildNodes;
	//出力層ノード数
	int			        m_numParentNodes;
	//入力と隠れ層するノードの重み
	float**             m_weights;
	//重みの調整
	float**             m_weightChanges;
	//計算結果の値
	float*              m_neuronValues;
	//ターゲット値を格納
	float*              m_desiredValues;
	//エラー
	float*              m_errors;
	//バイアスの重み
	float*              m_biasWeights;
	//バイアス値
	float*              m_biasValues;
	//重みの調整を計算する学習率を保持
	float		        m_learningRate;
	//線形活性化関数使用（デフォfalse）
	bool		        m_linearOutput;
	//モーメンタム使用（デフォfalse）
	bool		        m_useMomentum;
	//前述モーメンタム因数を保持（モーメント使用時のみ使用）
	float		        m_momentumFactor;
	//親層を格納(入力層の場合NULL)
	NeuralNetworkLayer* m_parentLayer;
	//子層を格納(出力層の場合NULL)
	NeuralNetworkLayer* m_childLayer;

public:
	//コンストラクタ
	NeuralNetworkLayer();
	//初期化
	void Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
	//メモリー解放
	void CleanUp();
	// 学習を開始するときだけ呼ぶ
	void RandomizeWeights();
	// エラー方程式をそれぞれに代入
	void CalculateErrors();
	// 重みを調整
	void AdjustWeights();
	// 全ての重みの計算
	void CalculateNeuronValues();

};

class NeuralNetwork
{
public:
	//入力層
	NeuralNetworkLayer	m_inputLayer;
	//隠れ層
	NeuralNetworkLayer	m_hiddenLayer;
	//出力層
	NeuralNetworkLayer	m_outputLayer;

public:
	// 初期化
	void Initialize(int nodesInput, int nodesHidden, int nodesOutput);
	//メモリー解放
	void CleanUp();
	//入力を設定
	void SetInput(int i, float value);
	//出力値
	float GetOutput(int i);
	//望ましい値を設定
	void SetDesiredOutput(int i, float value);
	//重みの計算
	void FeedForward();
	//出力と隠れ層のエラーをもとに入力値と隠れ層の重みを調整
	void BackPropagate();
	//出力層のもっとも高いものを判断する
	int  GetMaxOutputID();
	//出力値と望ましい値の集合に関係するエラー
	float CalculateError();
	//学習率を設定
	void SetLearningRate(float rate);
	//線形活性化関数を使うか設定
	void SetLinearOutput(bool linear);
	//モーメントを設定
	void SetMomentum(bool momentum, float factor);
	//データを出力
	void DumpData(char* filename);
	//学習データを入力
	void LearningDataInput(char* filename);

};