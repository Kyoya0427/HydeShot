//======================================================
// File Name	: NeuralNetwork.h
// Summary		: ニューラルネットワーク
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


class NeuralNetworkLayer
{
public:
	int			NumberOfNodes;
	int			NumberOfChildNodes;
	int			NumberOfParentNodes;
	float** Weights;
	float** WeightChanges;
	float* NeuronValues;
	float* DesiredValues;
	float* Errors;
	float* BiasWeights;
	float* BiasValues;
	float		LearningRate;

	bool		LinearOutput;
	bool		UseMomentum;
	float		MomentumFactor;

	NeuralNetworkLayer* ParentLayer;
	NeuralNetworkLayer* ChildLayer;

	NeuralNetworkLayer();

	void	Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
	void	CleanUp(void);
	void	RandomizeWeights(void);
	void	CalculateErrors(void);
	void	AdjustWeights(void);
	void	CalculateNeuronValues(void);

};

// Implements a 3-Layer neural network with one input layer, one hidden layer, and one output layer
class NeuralNetwork
{
public:
	NeuralNetworkLayer	InputLayer;
	NeuralNetworkLayer	HiddenLayer;
	NeuralNetworkLayer	OutputLayer;

	void	Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
	void	CleanUp();
	void	SetInput(int i, float value);
	float	GetOutput(int i);
	void	SetDesiredOutput(int i, float value);
	void	FeedForward(void);
	void	BackPropagate(void);
	int		GetMaxOutputID(void);
	float	CalculateError(void);
	void	SetLearningRate(float rate);
	void	SetLinearOutput(bool useLinear);
	void	SetMomentum(bool useMomentum, float factor);
	void	DumpData(char* filename);


};

//class NeuralNetwork
//{
//private:
//	class NeuralNetworkLayer
//	{
//		using DataType = float;
//		using DataArray = std::unique_ptr<DataType[]>;
//		using DataArray2d = std::unique_ptr<DataArray[]>;
//
//	public:
//		//入力層ノード数
//		int			                      m_numNodes;
//		//隠れ層ノード数
//		int			                      m_numChildNodes;
//		//出力層ノード数
//		int			                      m_numParentNodes;
//		//入力と隠れ層するノードの重み
//		DataArray2d  m_weights;
//		//重みの調整
//		DataArray2d  m_weightChanges;
//		//計算結果の値
//		DataArray               m_neuronValues;
//		//ターゲット値を格納
//		DataArray               m_desiredValues;
//		//エラー
//		DataArray               m_errors;
//		//バイアスの重み
//		DataArray               m_biasWeights;
//		//バイアス値
//		DataArray               m_biasValues;
//		//重みの調整を計算する学習率を保持
//		DataType		                      m_learningRate;
//		//線形活性化関数使用（デフォfalse）
//		bool		                      m_linearOutput;
//		//モーメンタム使用（デフォfalse）
//		bool		                      m_useMomentum;
//		//前述モーメンタム因数を保持（モーメント使用時のみ使用）
//		DataType		                      m_momentumFactor;
//		//親層を格納(入力層の場合NULL)
//		NeuralNetworkLayer* m_parentLayer;
//		//子層を格納(出力層の場合NULL)
//		NeuralNetworkLayer* m_childLayer;
//
//	public:
//		//コンストラクタ
//		NeuralNetworkLayer();
//		//初期化
//		void Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
//		//メモリー解放
//		void CleanUp();
//		// 学習を開始するときだけ呼ぶ
//		void RandomizeWeights();
//		// エラー方程式をそれぞれに代入
//		void CalculateErrors();
//		// 重みを調整
//		void AdjustWeights();
//		// 全ての重みの計算
//		void CalculateNeuronValues();
//
//	};
//public:
//	//入力層
//	NeuralNetworkLayer	m_inputLayer;
//	//隠れ層
//	NeuralNetworkLayer	m_hiddenLayer;
//	//出力層
//	NeuralNetworkLayer	m_outputLayer;
//	// 初期化
//	void Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
//	//メモリー解放
//	void CleanUp();
//	//入力を設定
//	void SetInput(int i, float value);
//	//出力値
//	float GetOutput(int i);
//	//望ましい値を設定
//	void SetDesiredOutput(int i, float value);
//	//重みの計算
//	void FeedForward();
//	//出力と隠れ層のエラーをもとに入力値と隠れ層の重みを調整
//	void BackPropagate();
//	//出力層のもっとも高いものを判断する
//	int	GetMaxOutputID();
//	//出力値と望ましい値の集合に関係するエラー
//	float CalculateError();
//	//学習率を設定
//	void SetLearningRate(float rate);
//	//線形活性化関数を使うか設定
//	void SetLinearOutput(bool useLinear);
//	//モーメントを設定
//	void SetMomentum(bool useMomentum, float factor);
//	//データを出力
//	void DumpData(char* filename);
//
//};