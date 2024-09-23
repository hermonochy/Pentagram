#pragma once

#include <stdint.h>
#include <string>

struct GladGLContext;
struct ImVec2;

namespace PNT {
    class image {
    private:
        GladGLContext* m_openglContext;
        uint32_t m_width, m_height, m_channels;
        unsigned char* m_pixels;
        unsigned int m_textureID;

    public:
        /// @brief Image object constructor.
        /// @param openglContext The desired OpenGL context to put the image in.
        image(GladGLContext* openglContext);

        /// @brief Image object constructor.
        /// @param path The desired image path.
        /// @param openglContext The desired OpenGL context to put the image in.
        image(const char* path, GladGLContext* openglContext);

        image(const image& original);

        ~image();

        /// @brief Loads an image from disk.
        /// @param path Image path on disk.
        void load(const char* path);

        /// @brief Loads an image from disk.
        /// @param path Image path on disk.
        void load(std::string path);

        /// @brief Creates an ImGui draw call for the image (Requires loadOnGPU()).
        /// @param dimensions The desired display width and height for the image in "ImVec2" format.
        void ImGuiDraw(ImVec2 dimensions) const;

        /// @brief Creates an ImGui draw call for the image (Requires loadOnGPU()).
        /// @param width The desired display width for the image.
        /// @param height The desired display height for the image.
        void ImGuiDraw(uint32_t width, uint32_t height) const;

        /// @brief Set the settings for the GPU texture (Requires loadOnGPU()).
        /// @param min Texture filtering for minification.
        /// @param mag Texture filtering for magmification.
        /// @param S Horizontal wrapping mode.
        /// @param T Vertical wrapping mode.
        void imageSettings(unsigned int min, unsigned int mag, unsigned int S, unsigned int T);

        /// @brief Loads the image on to the GPU.
        void loadOnGPU();

        /// @brief Unloads the texture off GPU.
        void unloadOffGPU();

        /// @brief Gets the texture ID.
        /// @return Returns the GPU texture ID (0 means not on GPU).
        uint32_t getID() const;

        /// @brief Get the image width.
        /// @return Returns the width of the image.
        uint32_t getWidth() const;

        /// @brief Get the image height.
        /// @return Returns the height of the image.
        uint32_t getHeight() const;

        /// @brief Gets the image pixels.
        /// @return Returns the pixel data for the image (DO NOT MODIFY).
        unsigned char* getPixels() const;

        /// @brief Checks the state of the image.
        /// @return The state of the image, true for valid and false for invalid (null).
        bool valid() const;
    };
}
