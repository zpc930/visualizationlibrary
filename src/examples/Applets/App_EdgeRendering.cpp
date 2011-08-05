/**************************************************************************************/
/*                                                                                    */
/*  Visualization Library                                                             */
/*  http://www.visualizationlibrary.org                                               */
/*                                                                                    */
/*  Copyright (c) 2005-2010, Michele Bosi                                             */
/*  All rights reserved.                                                              */
/*                                                                                    */
/*  Redistribution and use in source and binary forms, with or without modification,  */
/*  are permitted provided that the following conditions are met:                     */
/*                                                                                    */
/*  - Redistributions of source code must retain the above copyright notice, this     */
/*  list of conditions and the following disclaimer.                                  */
/*                                                                                    */
/*  - Redistributions in binary form must reproduce the above copyright notice, this  */
/*  list of conditions and the following disclaimer in the documentation and/or       */
/*  other materials provided with the distribution.                                   */
/*                                                                                    */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND   */
/*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE            */
/*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR  */
/*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    */
/*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      */
/*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    */
/*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS     */
/*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      */
/*                                                                                    */
/**************************************************************************************/

#include "BaseDemo.hpp"
#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/EdgeExtractor.hpp>
#include <vlGraphics/EdgeRenderer.hpp>

using namespace vl;

class App_EdgeRendering: public BaseDemo
{
public:
  virtual String appletInfo()
  {
    return BaseDemo::appletInfo() + 
    "- '1' = edge rendering off.\n" +
    "- '2' = edge rendering on: silhouette only.\n" +
    "- '3' = edge rendering on: silhouette + creases.\n" +
    "- '4' = edge rendering on: silhouette + creases + hidden lines.\n" +
    "- '5' = edges only: silhouette + creases.\n" + 
    "- '6' = edges only: silhouette + creases + hidden lines.\n" +
    "\n";
  }

  void initEvent()
  {
    vl::Log::notify(appletInfo());

    // retrieve the default rendering
    mMainRendering = rendering()->as<Rendering>();
    // retrieve the default renderer, which we'll use as the solid-renderer
    mSolidRenderer = mMainRendering->renderer();

    // create our EdgeRenderer
    mEdgeRenderer = new EdgeRenderer;
    // we set the clear flags to be CF_CLEAR_DEPTH (by default is set to CF_CLEAR_COLOR_DEPTH) because 
    // when the wireframe rendering starts we want to preserve the color-buffer as generated by the solid 
    // rendering but we want to clear the Z-buffer as it is needed by the hidden-line-removal algorithm 
    // implemented by EdgeRenderer.
    mEdgeRenderer->setClearFlags(CF_CLEAR_DEPTH);
    // target the same opengl window
    mEdgeRenderer->setRenderTarget(mSolidRenderer->renderTarget());
    // enqueue the EdgeRenderer in the rendering, will be executed after mSolidRenderer
    mMainRendering->renderers().push_back( mEdgeRenderer.get() );

    // hidden line and crease options
    mEdgeRenderer->setShowHiddenLines(true);
    mEdgeRenderer->setShowCreases(true);
    mEdgeRenderer->setCreaseAngle(35.0f);

    // style options
    mEdgeRenderer->setLineWidth(2.0f);
    mEdgeRenderer->setSmoothLines(true);
    mEdgeRenderer->setDefaultLineColor(black);

    // fills the scene with a few actors.
    // the beauty of this system is that you setup your actors ony once in a single scene managers and
    // they will be rendered twice, first using a normal renderer and then using the edge renderer.
    setupScene();
  }

  // populates the scene
  void setupScene()
  {
    // setup common states
    ref<Light> camera_light = new Light(0);
    ref<EnableSet> enables = new EnableSet;
    enables->enable(EN_DEPTH_TEST);
    enables->enable(EN_LIGHTING);

    // red material fx
    ref<Effect> red_fx = new Effect;
    red_fx->shader()->setEnableSet(enables.get());
    red_fx->shader()->gocMaterial()->setDiffuse(red);
    red_fx->shader()->setRenderState(camera_light.get());

    // green material fx
    ref<Effect> green_fx = new Effect;
    green_fx->shader()->setEnableSet(enables.get());
    green_fx->shader()->gocMaterial()->setDiffuse(green);
    green_fx->shader()->setRenderState(camera_light.get());

    // blue material fx
    ref<Effect> yellow_fx = new Effect;
    yellow_fx->shader()->setEnableSet(enables.get());
    yellow_fx->shader()->gocMaterial()->setDiffuse(yellow);
    yellow_fx->shader()->setRenderState(camera_light.get());

    // add box, cylinder, cone actors to the scene
    ref<Geometry> geom1 = makeBox     (vec3(-7,0,0),5,5,5);
    ref<Geometry> geom2 = makeCylinder(vec3(0,0,0), 5,5, 10,2, true, true);
    ref<Geometry> geom3 = makeCone    (vec3(+7,0,0),5,5, 20, true);

    // needed since we enabled the lighting
    geom1->computeNormals();
    geom2->computeNormals();
    geom3->computeNormals();

    // add the actors to the scene
    sceneManager()->tree()->addActor( geom1.get(), red_fx.get(),    mMainRendering->transform() );
    sceneManager()->tree()->addActor( geom2.get(), green_fx.get(),  mMainRendering->transform() );
    sceneManager()->tree()->addActor( geom3.get(), yellow_fx.get(), mMainRendering->transform() );
  }

  // user controls:
  // '1' = edge rendering off.
  // '2' = edge rendering on: silhouette only.
  // '3' = edge rendering on: silhouette + creases.
  // '4' = edge rendering on: silhouette + creases + hidden lines.
  // '5' = edges only: silhouette + creases.
  // '6' = edges only: silhouette + creases + hidden lines.
  void keyPressEvent(unsigned short ch, EKey key)
  {
    BaseDemo::keyPressEvent(ch, key);

    if (ch == '1')
    {
      mSolidRenderer->setEnableMask(0xFFFFFFFF);
      mEdgeRenderer->setEnableMask(0);
      Log::print("Edge rendering disabled.\n");
    }
    else
    if (ch == '2')
    {
      mSolidRenderer->setEnableMask(0xFFFFFFFF);
      // preserve color buffer, clear depth buffer
      mEdgeRenderer->setClearFlags(CF_CLEAR_DEPTH);
      mEdgeRenderer->setEnableMask(0xFFFFFFFF);
      mEdgeRenderer->setShowCreases(false);
      mEdgeRenderer->setShowHiddenLines(false);
      Log::print("Edge rendering enabled. Creases = off, hidden lines = off.\n");
    }
    else
    if (ch == '3')
    {
      mSolidRenderer->setEnableMask(0xFFFFFFFF);
      // preserve color buffer, clear depth buffer
      mEdgeRenderer->setClearFlags(CF_CLEAR_DEPTH);
      mEdgeRenderer->setEnableMask(0xFFFFFFFF);
      mEdgeRenderer->setShowCreases(true);
      mEdgeRenderer->setShowHiddenLines(false);
      Log::print("Edge rendering enabled. Creases = on, hidden lines = off.\n");
    }
    else
    if (ch == '4')
    {
      mSolidRenderer->setEnableMask(0xFFFFFFFF);
      // preserve color buffer, clear depth buffer
      mEdgeRenderer->setClearFlags(CF_CLEAR_DEPTH);
      mEdgeRenderer->setEnableMask(0xFFFFFFFF);
      mEdgeRenderer->setShowCreases(true);
      mEdgeRenderer->setShowHiddenLines(true);
      Log::print("Edge rendering enabled. Creases = on, hidden lines = on.\n");
    }
    else
    if (ch == '5')
    {
      mSolidRenderer->setEnableMask(0);
      // clear color and depth buffer
      mEdgeRenderer->setClearFlags(CF_CLEAR_COLOR_DEPTH);
      mEdgeRenderer->setEnableMask(0xFFFFFFFF);
      mEdgeRenderer->setShowCreases(true);
      mEdgeRenderer->setShowHiddenLines(false);
      Log::print("Hidden line removal wireframe enabled. Creases = on, hidden lines = off.\n");
    }
    if (ch == '6')
    {
      mSolidRenderer->setEnableMask(0);
      // clear color and depth buffer
      mEdgeRenderer->setClearFlags(CF_CLEAR_COLOR_DEPTH);
      mEdgeRenderer->setEnableMask(0xFFFFFFFF);
      mEdgeRenderer->setShowCreases(true);
      mEdgeRenderer->setShowHiddenLines(true);
      Log::print("Hidden line removal wireframe enabled. Creases = on, hidden lines = on.\n");
    }
  }

  void resizeEvent(int w, int h)
  {
    Camera* camera = mMainRendering->camera();
    camera->viewport()->setWidth ( w );
    camera->viewport()->setHeight( h );
    camera->setProjectionAsPerspective();
  }

  void loadModel(const std::vector<String>& files)
  {
    // resets the scene
    sceneManager()->tree()->actors()->clear();
    // resets the EdgeRenderer cache
    mEdgeRenderer->clearCache();

    for(unsigned int i=0; i<files.size(); ++i)
    {
      ref<ResourceDatabase> resource_db = loadResource(files[i],true);

      if (!resource_db || resource_db->count<Actor>() == 0)
      {
        Log::error("No data found.\n");
        continue;
      }

      std::vector< ref<Actor> > actors;
      resource_db->get<Actor>(actors);
      for(unsigned i=0; i<actors.size(); ++i)
      {
        ref<Actor> actor = actors[i].get();
        // define a reasonable Shader
        actor->effect()->shader()->setRenderState( new Light(0) );
        actor->effect()->shader()->enable(EN_DEPTH_TEST);
        actor->effect()->shader()->enable(EN_LIGHTING);
        actor->effect()->shader()->gocLightModel()->setTwoSide(true);
        // add the actor to the scene
        sceneManager()->tree()->addActor( actor.get() );
      }
    }

    // position the camera to nicely see the objects in the scene
    trackball()->adjustView( sceneManager(), vec3(0,0,1)/*direction*/, vec3(0,1,0)/*up*/, 1.0f/*bias*/ );
  }

  // laod the files dropped in the window
  void fileDroppedEvent(const std::vector<String>& files) { loadModel(files); }

protected:
  ref< Renderer > mSolidRenderer;
  ref< EdgeRenderer > mEdgeRenderer;
  ref<Rendering> mMainRendering;
};

// Have fun!

BaseDemo* Create_App_EdgeRendering() { return new App_EdgeRendering; }
