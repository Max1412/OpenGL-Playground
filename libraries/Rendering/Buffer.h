#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <vector>

#include "Utils/UtilCollection.h"

class Buffer
{
public:
	Buffer();

	GLuint getHandle();

	void bind() const;

	void bindBase(unsigned int binding);

	void del();

	template<typename T>
	void setData(const std::vector<T> &data, GLenum target,  GLenum drawType);

	template<typename T, std::size_t N>
	void setData(const std::array<T, N> &data, GLenum target, GLenum drawType);

	template<typename T>
	void setStorage(const std::vector<T> &data, GLenum target, GLbitfield flags);

	template<typename T, std::size_t N>
	void setStorage(const std::array<T, N> &data, GLenum target, GLbitfield flags);

	template<typename T>
	void setSubData(const std::vector<T> &data, GLenum target, int offset);

	template<typename T, std::size_t N>
	void setSubData(const std::array<T, N> &data, GLenum target, int offset);

    template<typename S>
    void setPartialContentMapped(const S& data, int startOffset, int size);

private:
	GLuint m_bufferHandle;
	GLenum m_target;

	bool m_isImmutable = false;


};

/*
*  Template function must be implemented in the header (whyyyy)
*/

template<typename S>
void Buffer::setPartialContentMapped(const S& data, int startOffset, int size) {
    bind();
    S* ptr = static_cast<S*>(glMapBufferRange(m_target, startOffset, size, GL_MAP_WRITE_BIT));
    *ptr = data;
    glUnmapBuffer(m_target);
}

template <typename T>
void Buffer::setData(const std::vector<T> &data, GLenum target, GLenum drawType) {
	if (m_isImmutable)
		throw std::runtime_error("Buffer is immutable, cannot reassign buffer data");
	m_target = target;
	glBindBuffer(target, m_bufferHandle);
	glBufferData(target, data.size() * sizeof(T), data.data(), drawType);
}

template <typename T, std::size_t N>
void Buffer::setData(const std::array<T, N> &data, GLenum target, GLenum drawType) {
	if (m_isImmutable)
		throw std::runtime_error("Buffer is immutable, cannot reassign buffer data");
	m_target = target;
	glBindBuffer(target, m_bufferHandle);
	glBufferData(target, data.size() * sizeof(T), data.data(), drawType);
}

template<typename T>
void Buffer::setSubData(const std::vector<T> &data, GLenum target, int offset) {
	if (m_isImmutable)
		throw std::runtime_error("Buffer is immutable, cannot reassign buffer data");
	m_target = target;
	glBindBuffer(target, m_bufferHandle);
	glBufferSubData(target, offset, data.size() * sizeof(T), data.data());
}

template <typename T, std::size_t N>
void Buffer::setSubData(const std::array<T, N> &data, GLenum target, int offset) {
	if (m_isImmutable)
		throw std::runtime_error("Buffer is immutable, cannot reassign buffer data");
	m_target = target;
	glBindBuffer(target, m_bufferHandle);
	glBufferSubData(target, offset, data.size() * sizeof(T), data.data());
}

template<typename T>
void Buffer::setStorage(const std::vector<T> &data, GLenum target, GLbitfield flags) {
	m_target = target;
	glBindBuffer(target, m_bufferHandle);
	glBufferStorage(target, data.size() * sizeof(T), data.data(), flags);
	m_isImmutable = true;

}

template <typename T, std::size_t N>
void Buffer::setStorage(const std::array<T, N> &data, GLenum target, GLbitfield flags) {
	m_target = target;
	glBindBuffer(target, m_bufferHandle);
	glBufferStorage(target, data.size() * sizeof(T), data.data(), flags);
	m_isImmutable = true;

}