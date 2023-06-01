#pragma once
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <type_traits>

#include "ccTypes.h"
#include "CCVector.h"
#include "math/Vec2.h"
#include "network/HttpRequest.h"
#include "fmt/format.h"

namespace ax
{
	class Label; 
	class Menu;
	class Node;
	namespace network
	{
		ccHttpRequestCallback;
	}
}


enum IconType {
	kIconTypeCube		= 0,
	kIconTypeShip		= 1,
	kIconTypeBall		= 2,
	kIconTypeUfo		 = 3,
	kIconTypeWave		= 4,
	kIconTypeRobot	   = 5,
	kIconTypeSpider	  = 6,
	kIconTypeSwing	   = 7,
	kIconTypeDeathEffect = 98,
	kIconTypeSpecial	 = 99,
};

enum popTransition {
	kTransitionFade = 0,
	kTransitionShop
};

//general purpose namespace for helper functions that can be useful with any class at any moment
namespace GameToolbox
{
	enum GTRes {
		Low = 0,
		Medium,
		High
	};
	
	void popSceneWithTransition(float time, popTransition type = kTransitionFade);
	void limitLabelWidth(ax::Label* label, float width, float normalScale, float minScale = 0);
	ax::Label* createBMFont(std::string text, std::string font);
	ax::Label* createBMFont(std::string text, std::string font, int width);
	ax::Label* createBMFont(std::string text, std::string font, int width, ax::TextHAlignment alignment);
	const char* lengthString(int len);
	int randomInt(int min, int max);
	int randomInt(int max);
	float randomFloat(int min, int max);
	float randomFloat(int max);
	
	ax::Color3B colorForIdx(int col);
	const char* getNameGamemode(IconType mode);
	int getValueForGamemode(IconType mode);

	ax::Color3B randomColor3B();
	std::string getTextureString(std::string texture);
	void alignItemsInColumnsWithPadding(ax::Menu* menu, const int rows, const int x_padding, const int y_padding);
	void alignItemsVerticallyWithPadding(ax::Vector<ax::Node*> children, float padding);
	void alignItemsHorizontally(ax::Vector<ax::Node*> children, float padding, ax::Point location);
	void alignItemsHorizontallyWithPadding(ax::Vector<ax::Node*> children, float padding);
	void createBG(ax::Node* layer, ax::Color3B color);
	void createBG(ax::Node* layer);
	void createCorners(ax::Node* layer, bool topRight, bool topLeft, bool botLeft, bool botRight);
	inline void createAllCorners(ax::Node* self) { return createCorners(self, true, true, true, true); }
	std::string getFileContentsResources(std::string_view file);
	
	float SquareDistance(float xa, float ya, float xb, float yb);
	float SquareDistance(ax::Vec2 a, ax::Vec2 b);

	float iLerp(float a, float b, float ratio, float dt);

	float slerp(float a, float b, float ratio);
	float iSlerp(float a, float b, float ratio, float dt);
	float repeat(float a, float length);

	std::optional<std::string> getResponse(ax::network::HttpResponse* response);
	
	std::vector<std::string> splitByDelim(const std::string& s, char delim);
	std::vector<std::string_view> splitByDelimStringView(std::string_view str, char delim);
	
	float stof(const std::string_view str);
	int stoi(const std::string_view str);
	
	void executeHttpRequest(const std::string& url, const std::string& postData, ax::network::HttpRequest::Type type, const ax::network::ccHttpRequestCallback& callback);
	
	ax::Color3B hsvToRgb(const ax::HSV& hsv);

	ax::BlendFunc getBlending();

	std::string xorCipher(const std::string& message, const std::string& key);

	template <typename T>
	inline T inRange(T value, T min, T max) {
		return MIN(MAX(value, min), max);
	}
	
	template <typename... T>
		void log(fmt::format_string<T...> fmt, T&&... args) {
		return fmt::print("{}\n", fmt::format(fmt, std::forward<T>(args)...));
	}
	
};
