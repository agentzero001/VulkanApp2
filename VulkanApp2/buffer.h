#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <glm/gtx/hash.hpp>


struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3>  getAttributeDescriptions();


	//operator overriding to use the Vertex struct as key in the hash table (see loadModel)
	bool operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}



};


//the hash function for Vertex is implemented by specifying a template specialization for std::hash<T>.
//This is required to use Vertex as a key in the hash table of std::unordered_map
//note that the python equivalent of unordered_map is dict and 
//to reach the same behaviour in python to use your custom types as key in the hash table you would have to define __eq__ and __hash__.
namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			//some esoteric kind of bit hacking i guess
			return ((hash<glm::vec3>()(vertex.pos) 
				^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) 
				^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}


struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};



extern const std::vector<Vertex> vertices;
extern const std::vector<uint32_t> indices;

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicaldevice);

void createBuffer(VkDeviceSize size,
	VkBufferUsageFlags usage,
	VkMemoryPropertyFlags properties,
	VkBuffer& buffer,
	VkDeviceMemory& bufferMemory,
	VkDevice device,
	VkPhysicalDevice physicalDevice);

VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool, VkDevice device);

void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue graphicsQueue, VkDevice device, VkCommandPool commandPool);


void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkQueue graphicsQueue, VkDevice device, VkCommandPool commandPool);