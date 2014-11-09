#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "stdafx.hpp"

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        void setPosition(const b2Vec2& rPos);//world position
        void setZoom(float level);//multiple of each dimension to find new
        void setRotation(float radiansCCW);

        float getZoom() const;
        float getRotation() const;
        const sf::View& getView() const;

    protected:
    private:
        int m_zoomLevel;//current zoom between [1,16]
        sf::Vector2f m_standardSize;
        sf::View m_view;
};

#endif // CAMERA_HPP