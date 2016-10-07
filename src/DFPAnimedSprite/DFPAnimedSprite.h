#ifndef AnimedSprite_H
#define AnimedSprite_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Sprite.h"
#include "SceneContainer.h"


namespace dfp
{
    class Animations;
    class Anim;
    class Sprite;
}


namespace dfp
{
	m2dkit::shared_ptr<m2dkit::core::CSprite> CreateDFPNode(	std::string animFile,
						m2dkit::core::CSceneContainer* sc,
						uint32 sceneId,
						const char* parentHierachyPath);


    /** This Class is designed to load and store animations, sprites and textures for them.
    * Also, this class can update and draw the current animation.*/
    class DFPAnimedSprite
    {
		friend m2dkit::shared_ptr<m2dkit::core::CSprite> CreateDFPNode(	std::string animFile,
									m2dkit::core::CSceneContainer* sc,
									uint32 sceneId,
									const char* parentHierachyPath);
    public:

        /** Constructor 
		* @param rendered is the main renderer object that is used to access the video driver.*/
		DFPAnimedSprite(std::map<std::string, std::shared_ptr<dfp::Animations> >& animationsColection,
			            std::map<std::string, std::shared_ptr<dfp::Sprite> >& spritesColection);

        /** The destructor */
        virtual ~DFPAnimedSprite();

        /** Enum used as a return code for Load function. */
        enum LoadAnimResult 
        { 
            /// everything is ok
            LOAD_ANIM_OK, 

            /// animations are not found
            LOAD_ANIM_NOT_FOWND,

            /// an unknown error occured
            LOAD_ANIM_ERROR 
        };

        /** Used to load a Dark Function Parser Animations file.
        * @param dfpAnimationFileName is the filename and path to the *.tmx file .
        * @return LoadMapResult type which can be LOAD_MAP_OK if the map was loaded succesfully.*/
        virtual LoadAnimResult Load(const std::string& dfpAnimationFileName);

		/** 
		* @param animSpeedFactor is a factor that will accelerate or slow-down the animation.
		*        Ex: if animSpeedFactor=2.0 the standard delay between animation-frames will be
		*        delay / 2.0. */
		void SetAnimSpeedFactor(float animSpeedFactor);


	protected:

		/** Check if the rectangle described by x,y,w,h are inside the view port
		* Override this function in derived classes. This function is used in Draw() tochec if
		* an object (described by a rectangle x,y,w,h) is on screen.
		* @param x is in pixels relative to the screen origin (left-up corner)
		* @param y is in pixels relative to the screen origin (left-up corner)
		* @param w is in pixels and is the width of the rectangle
		* @param h is in pixels and is the height of the rectangle
		* @return true if the rectangle is inside the screen or have some parts in the screen*/
		virtual bool IsInsideViewPort(int x, int y, int w, int h){ return true; }

		/**
		* Draw. All the "paint calls" must be placed in this function.
		* @param screenPosX is the current position in pixels relative to view port (aka screen).
		* @param screenPosY is the current position in pixels relative to view port (aka screen).
		* @param zoomFactor is a float used to specify the magnification of the draw. The default value is 1.0.*/
		void Draw(int screenPosX, int screenPosY, float zoomFactorX = 1.0, float zoomFactorY = 1.0);

    protected:


		/** Used as a Animations Resource collection to avoid loading the same Animation more times */
		std::map<std::string, std::shared_ptr<dfp::Animations> > m_dfpAnimationsColection;
        
        /** This object is an shared pointer to the Dark Function Parser Animation*/
        std::shared_ptr<dfp::Animations> m_dfpAnimations;

		/** Used as a Sprite Resource collection to avoid loading the same Sprite more times */
		std::map<std::string, std::shared_ptr<dfp::Sprite> > m_dfpSpritesColection;

        /** This object is an shared pointer to the Dark Function Parser Sprite */
        std::shared_ptr<dfp::Sprite> m_dfpSprite;

        /** This is the current animation of this instance. This animation will be displayed.*/
        std::shared_ptr<dfp::Anim> m_dfpCurrentAnim;

		float m_animSpeedFactor;

    };

}

#endif //AnimedSprite_H