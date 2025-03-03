#include "TrashTheCache.h"
#include "Component.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "implot.h"
#include <chrono>

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform;
	int ID;
};

class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

TrashTheCache::TrashTheCache(GameObject* owner):
	Component(owner)
{

	//MeasureInt(10);
	//MeasureGameObject(10);
	//MeasureGameObjectAlt(10);
}

void TrashTheCache::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	ImGui::Begin("Exercise 1");

	ImGui::InputInt("Sample Size", &m_SampleSizeInt);
	if (ImGui::Button("Trash The Cache Int"))
	{
		MeasureInt(m_SampleSizeInt);
	}
	if (not m_MeasurementsInt.empty())
	{
		if (ImPlot::BeginPlot("Trash The Cache int", ImVec2(250, 180)))
		{
			ImPlot::PlotLine("", &m_MeasurementsInt[0], 11);
			ImPlot::EndPlot();
		}
	}
	ImGui::End();

	ImGui::Begin("Exercise 2");

	ImGui::InputInt("Sample Size", &m_SampleSizeGameObject);
	if (ImGui::Button("Trash The Cache GameObject"))
	{
		MeasureGameObject(m_SampleSizeGameObject);
	}
	if (ImGui::Button("Trash The Cache GameObject Alt"))
	{
		MeasureGameObjectAlt(m_SampleSizeGameObject);
	}

	if (not m_MeasurementsGameObject.empty())
	{
		if (ImPlot::BeginPlot("Trash The Cache GameObject3D", ImVec2(250, 180)))
		{
			ImPlot::PlotLine("", &m_MeasurementsGameObject[0], 11);
			ImPlot::EndPlot();
		}
	}

	if (not m_MeasurementsGameObjectAlt.empty())
	{
		if (ImPlot::BeginPlot("Trash The Cache Alt GameObject3D", ImVec2(250, 180)))
		{
			ImPlot::PlotLine("", &m_MeasurementsGameObject[0], 11);
			ImPlot::EndPlot();
		}
	}

	if (not m_MeasurementsGameObject.empty() and not m_MeasurementsGameObjectAlt.empty())
	{
		if (ImPlot::BeginPlot("Trash The Cache Combined", ImVec2(250, 180)))
		{
			ImPlot::PlotLine("Default", &m_MeasurementsGameObjectAlt[0], 11);
			ImPlot::PlotLine("Alt", &m_MeasurementsGameObject[0], 11);
			ImPlot::EndPlot();
		}
	}

	ImGui::End();
}

void TrashTheCache::MeasureInt(int sampleSize)
{
	assert(sampleSize > 2);

	m_MeasurementsInt.resize(11);
	std::vector<int> dataVector{};
	dataVector.resize(m_BufferSize);

	std::vector<std::vector<long long>> results{};
	results.resize(sampleSize);

	for (int sampleIndex{}; sampleIndex < sampleSize; ++sampleIndex)
	{
		results[sampleIndex].resize(11);
		int stepIndex{};
		for (int stepSize{ 1 }; stepSize <= 1024; stepSize += stepSize)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (size_t index{ 0 }; index < dataVector.size(); index += stepSize)
			{
				dataVector[index] *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			results[sampleIndex][stepIndex] += total;
			stepIndex++;
		}
	}

	AverageResults(results, m_MeasurementsInt);
}

void TrashTheCache::MeasureGameObject(int sampleSize)
{
	assert(sampleSize > 2);

	m_MeasurementsGameObject.resize(11);
	std::vector<GameObject3D> dataVector{};
	dataVector.resize(m_BufferSize);

	std::vector<std::vector<long long>> results{};
	results.resize(sampleSize);

	for (int sampleIndex{}; sampleIndex < sampleSize; ++sampleIndex)
	{
		results[sampleIndex].resize(11);
		int stepIndex{};
		for (int stepSize{ 1 }; stepSize <= 1024; stepSize += stepSize)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (size_t index{ 0 }; index < dataVector.size(); index += stepSize)
			{
				dataVector[index].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			results[sampleIndex][stepIndex] += total;
			stepIndex++;
		}
	}

	AverageResults(results, m_MeasurementsGameObject);
}

void TrashTheCache::MeasureGameObjectAlt(int sampleSize)
{
	assert(sampleSize > 2);

	m_MeasurementsGameObjectAlt.resize(11);
	std::vector<GameObject3DAlt> dataVector{};
	dataVector.resize(m_BufferSize);

	std::vector<std::vector<long long>> results{};
	results.resize(sampleSize);

	for (int sampleIndex{}; sampleIndex < sampleSize; ++sampleIndex)
	{
		results[sampleIndex].resize(11);
		int stepIndex{};
		for (int stepSize{ 1 }; stepSize <= 1024; stepSize += stepSize)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (size_t index{ 0 }; index < dataVector.size(); index += stepSize)
			{
				dataVector[index].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			results[sampleIndex][stepIndex] += total;
			stepIndex++;
		}
	}

	AverageResults(results, m_MeasurementsGameObjectAlt);
}

void TrashTheCache::AverageResults(const std::vector<std::vector<long long>> results, std::vector<long long>& measurements)
{
	for (int stepIndex{}; stepIndex <= 10; ++stepIndex)
	{
		long long lowest{ LLONG_MAX };
		long long highest{};
		long long average{};

		for (size_t sampleIndex{}; sampleIndex < results.size(); ++sampleIndex)
		{
			long long currentMeasurement{ results[sampleIndex][stepIndex] };
			if (currentMeasurement < lowest) lowest = currentMeasurement;
			if (currentMeasurement > highest) highest = currentMeasurement;
			average += currentMeasurement;
		}
		average -= lowest + highest;
		average /= results.size() - 2;

		measurements[stepIndex] = average;
	}
}

