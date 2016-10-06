#include "DFPAnimedSprite.h"

#include "DarkFunctionParser/Sprite.h"
#include "DarkFunctionParser/Animations.h"


#include <vector>

#include "IwDebug.h"

namespace dfp
{
	DFPAnimedSprite::DFPAnimedSprite(
									 std::map<std::string, std::shared_ptr<dfp::Animations> >& animationsColection,
									 std::map<std::string, std::shared_ptr<dfp::Sprite> >& spritesColection)
		            : m_dfpAnimations(nullptr)
					, m_dfpAnimationsColection(animationsColection)
					, m_dfpSpritesColection(spritesColection)
					, m_dfpSprite(nullptr)	
					, m_animSpeedFactor(1.0)
    {
    }

    DFPAnimedSprite::~DFPAnimedSprite()
    {
    }

    DFPAnimedSprite::LoadAnimResult DFPAnimedSprite::Load(const std::string& dfpAnimationFileName)
    {
		/// Check if the animation file was already loaded.
		if (m_dfpAnimationsColection.find(dfpAnimationFileName) != m_dfpAnimationsColection.end())
		{
			/// Create a NEW animation instance starting from an animationthat was already loaded.
			/// The Animation from s_dfpAnimationColection is used as a sample that is copyed.
			m_dfpAnimations = std::make_shared<dfp::Animations>(m_dfpAnimationsColection[dfpAnimationFileName]);
		}
		else
		{
			/// If the animation was not found in the s_dfpAnimationColection, will be loaded, and added to that list.
			m_dfpAnimations = std::make_shared<dfp::Animations>();
			dfp::ParseResult result = m_dfpAnimations->ParseFile(dfpAnimationFileName);

			if (result != dfp::ParseResult::OK)
			{
				IwError(("Function '%s' (%s:%d) cannot load animation from file '%s'",
					__FUNCTION__, __FILE__, __LINE__, dfpAnimationFileName.c_str()));

				return LOAD_ANIM_ERROR;
			}

			m_dfpAnimationsColection[dfpAnimationFileName] = m_dfpAnimations;
		}

		if (m_dfpSpritesColection.find(m_dfpAnimations->GetSpriteFileName()) != m_dfpSpritesColection.end())
		{
			m_dfpSprite = m_dfpSpritesColection[m_dfpAnimations->GetSpriteFileName()];
		}
		else
		{
			m_dfpSprite = std::make_shared<dfp::Sprite>();
			dfp::ParseResult result = m_dfpSprite->ParseFile(m_dfpAnimations->GetSpriteFileName());

			if (result != dfp::ParseResult::OK)
			{
				IwError((
					"Function '%s' (%s:%d) cannot load sprite from file '%s'",
					__FUNCTION__, __FILE__, __LINE__, m_dfpAnimations->GetSpriteFileName().c_str()));

				return LOAD_ANIM_ERROR;
			}

			m_dfpSpritesColection[m_dfpAnimations->GetSpriteFileName()] = m_dfpSprite;
		}

		//if (s_texturesColection.find(m_dfpSprite->GetImageFileName()) != s_texturesColection.end())
		//{
		//	m_spriteTextures = s_texturesColection[m_dfpSprite->GetImageFileName()];
		//	return LOAD_ANIM_OK;
		//}

		//m_texturesColection[m_dfpSprite->GetImageFileName()]
        /*m_spriteTextures = std::make_shared<SDL_TextureC>(m_renderer, m_dfpSprite->GetImageFileName());
        if (!m_spriteTextures || !m_spriteTextures->m_tex)
        {
            SDL_LogMessage(
                SDL_LOG_CATEGORY_APPLICATION,
                SDL_LOG_PRIORITY_ERROR,
                "Function '%s' (%s:%d) cannot load texture from file '%s'",
                __FUNCTION__, __FILE__, __LINE__, m_dfpSprite->GetImageFileName().c_str());

            return LOAD_ANIM_ERROR;
        }*/

		//s_texturesColection[m_dfpSprite->GetImageFileName()] = m_spriteTextures;

        return LOAD_ANIM_OK;
    }

	void DFPAnimedSprite::SetAnimSpeedFactor(float animSpeedFactor)
	{
		m_animSpeedFactor = animSpeedFactor;
	}

   
	/*m2dkit::core::CNode::eState DFPAnimedSprite::Update(float dt)
    {
		m2dkit::core::CNode::eState state = m2dkit::core::CSprite::Update(dt);

		if (m_dfpCurrentAnim)
		{
			m_dfpCurrentAnim->Update(dt, m_animSpeedFactor);
		}

		return state;
    }*/

    void DFPAnimedSprite::Draw(int currentPosX, int currentPosY, float zoomFactorX, float zoomFactorY)
    {
        if (m_dfpCurrentAnim == nullptr)
            return;

        /// Get the current Cell. The current cell is constantly changed by the Update function.
        auto cell = m_dfpCurrentAnim->GetCurrentCell();
        if (!cell)
            return;

        /// Get the vector with all the small parts that compoze the sprite.
        auto cellsSpr = cell->GetCellsSpr();
        
        /// Draw all the small parts 
        /*for each (auto cs in cellsSpr)
        {
            std::shared_ptr<dfp::Spr> sp = m_dfpSprite->GetSpr(cs->GetName());
           
            SDL_Rect src = { sp->GetX(), sp->GetY(), sp->GetW(), sp->GetH() };
            
			SDL_Rect dst = { 
				cs->GetX() * zoomFactorX + currentPosX - sp->GetW() * zoomFactorX / 2,
				cs->GetY() * zoomFactorY + currentPosY - sp->GetH() * zoomFactorY / 2,
                (int)(sp->GetW() * zoomFactorX), 
                (int)(sp->GetH() * zoomFactorY) };

			if (!IsInsideViewPort(dst.x, dst.y, dst.w, dst.h))
				continue;

            SDL_RenderCopy(m_renderer, m_spriteTextures->m_tex, &src, &dst);
        
            #if defined(_DEBUG)
            static int change = 1;
            change++;
            SDL_Rect absRect = { currentPosX-2, currentPosY-2, 4, 4 };
            SDL_SetRenderDrawColor(m_renderer, change, 0, 255, 255);
			SDL_RenderFillRect(m_renderer, &absRect);
            #endif
        }*/
    }


	//void DFPAnimedSprite::DrawImpl(m2dkit::core::CRender& nodeRenderer)
	//{
	//	m2dkit::core::CSprite::DrawImpl(nodeRenderer);

	//	//Draw(this->m_X, this->m_Y, this->m_ScaleX, this->m_ScaleY);
	//}

	bool CreateDFPNode(	std::string animFile,
						m2dkit::core::CSceneContainer* sc,
						uint32 sceneId,
						const char* parentHierachyPath)
	{
		/// Example of how to load an "dark function parser" animation type
		/// the bellow two maps are global storrage for all loadded sprites
		std::map<std::string, std::shared_ptr<dfp::Animations> > dfpAnimationsColection;
		std::map<std::string, std::shared_ptr<dfp::Sprite> > dfpSpritesColection;

		std::shared_ptr<dfp::DFPAnimedSprite> dfpa = std::make_shared<dfp::DFPAnimedSprite>(dfpAnimationsColection, dfpSpritesColection);

		if (dfpa->Load(animFile) == dfp::DFPAnimedSprite::LoadAnimResult::LOAD_ANIM_OK)
		{
			m2dkit::core::CScene* scene = sc->GetScene(sceneId);

			//m2dkit::core::CSpriteCreationParams params;
			//params.m_Name = "Sprite1";
			//params.m_Dimensions = CIwFVec2(128.0f, 128.0f);
			//params.m_Position = CIwFVec2(256.f, 128.0f);
			//params.m_Pivot = CIwFVec2(0.5f, 0.5f);
			////params.m_SpriteFrame = scene->CreateSpriteFrame("assets/barrel.png", "barrel1", CIwRect32(0, 0, 0, 0));
			//m2dkit::shared_ptr<m2dkit::core::CSprite> sprite = sc->CreateNode<m2dkit::core::CSprite>(params, sceneId, parentHierachyPath);

			

			for each (auto animIterator in dfpa->m_dfpAnimations->GetAnims())
			{
				std::shared_ptr<Anim> anim = animIterator.second;
				
				for each (auto cell in anim->GetCells())
				{
					auto cellsSpr = cell->GetCellsSpr();
					for each (auto cs in cellsSpr)
					{
						std::shared_ptr<dfp::Spr> sp = dfpa->m_dfpSprite->GetSpr(cs->GetName());

					
						m2dkit::core::CSpriteCreationParams params;
						//params.m_Name = "Sprite1";
						params.m_Dimensions = CIwFVec2(128.0f, 128.0f);
						params.m_Position = CIwFVec2(256.f, 128.0f);
						params.m_Pivot = CIwFVec2(0.5f, 0.5f);
						params.m_SpriteFrame = scene->CreateSpriteFrame(dfpa->m_dfpSprite->GetImageFileName(), cs->GetName(), CIwRect32(sp->GetX(), sp->GetY(), sp->GetW(), sp->GetH()));
						m2dkit::shared_ptr<m2dkit::core::CSprite> sprite = sc->CreateNode<m2dkit::core::CSprite>(params, sceneId, parentHierachyPath);

						/*
						SDL_Rect src = { sp->GetX(), sp->GetY(), sp->GetW(), sp->GetH() };

						SDL_Rect dst = {
							cs->GetX() * zoomFactorX + currentPosX - sp->GetW() * zoomFactorX / 2,
							cs->GetY() * zoomFactorY + currentPosY - sp->GetH() * zoomFactorY / 2,
							(int)(sp->GetW() * zoomFactorX),
							(int)(sp->GetH() * zoomFactorY) };

						if (!IsInsideViewPort(dst.x, dst.y, dst.w, dst.h))
							continue;

						SDL_RenderCopy(m_renderer, m_spriteTextures->m_tex, &src, &dst);

						#if defined(_DEBUG)
						static int change = 1;
						change++;
						SDL_Rect absRect = { currentPosX - 2, currentPosY - 2, 4, 4 };
						SDL_SetRenderDrawColor(m_renderer, change, 0, 255, 255);
						SDL_RenderFillRect(m_renderer, &absRect);
						#endif
						*/
					}
				}
			}
		}


		return true;
	}

}