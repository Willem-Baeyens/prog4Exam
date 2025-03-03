#pragma once
#include "Component.h"
#include <vector>
class TrashTheCache final : public Component
{
public:
	TrashTheCache(GameObject* owner);

	void virtual Render() override;

private:
	void MeasureInt(int sampleSize);
	void MeasureGameObject(int sampleSize);
	void MeasureGameObjectAlt(int sampleSize);

	void AverageResults(const std::vector<std::vector<long long>> results, std::vector<long long>& measurements);

	std::vector<long long> m_MeasurementsInt;
	std::vector<long long> m_MeasurementsGameObject;
	std::vector<long long> m_MeasurementsGameObjectAlt;

	int m_SampleSizeInt{ 10 };
	int m_SampleSizeGameObject{ 10 };


	const int m_BufferSize{ 67108864 }; //2^26
};