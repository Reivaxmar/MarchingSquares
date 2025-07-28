#include <iostream>
using namespace std;

#include "MarchingSquares.h"
#include "ObjectUtils.h"
#include "FunctionHandler.h"
#include "Utils.h"
#include "ViewController.h"
#include "Grid.h"
#include "SceneObject.h"
#include "Scene.h"
#include <cmath>
#include "external/PerlinNoise.hpp"

int main() {
    // The main window
    RenderWindow window(VideoMode(1200, 675), "Marching Squares", 7U, ContextSettings(0, 0, 8));
    window.setFramerateLimit(60);

    siv::PerlinNoise noise(12345); // Seed can be any value

    // List of events
    vector<Event> events;

    // Current view
    View view = window.getDefaultView();
    view.setCenter(Vector2f(0, 0));
    view.zoom(0.1);

    // A controller for moving the camera
    ViewController controller(view);

    // The main scene
    Scene scene;

    // Add the grid
    scene.addObject(make_shared<Grid>(view));
    // And the Marching Squares
    // scene.addObject(make_shared<MarchingSquares>(FunctionHandler([](double x, double y) {
    //     x /= 6.0; y /= 6.0; // Scale inputs
    //     double a = 1.0, k = 4.0;
    //     double r = std::sqrt(x * x + y * y);
    //     double theta = std::atan2(y, x);
    //     return r - a * std::sin(k * theta);
    // }), 0.5));
    // Create the Marching Squares pointer
    shared_ptr<MarchingSquares> MS_ptr = make_shared<MarchingSquares>(FunctionHandler([&noise](double x, double y) {
        const int octaves = 5;         // Number of noise layers
        const double persistence = 0.5; // Amplitude decrease factor per octave
        const double lacunarity = 2.0;  // Frequency increase factor per octave

        double amplitude = 1.0;
        double frequency = 1.0;
        double noiseHeight = 0.0;

        // Normalize coordinates to control base frequency
        x /= 10.0;
        y /= 10.0;

        for (int i = 0; i < octaves; ++i) {
            noiseHeight += amplitude * noise.noise2D(x * frequency, y * frequency);

            amplitude *= persistence;
            frequency *= lacunarity;
        }

        return noiseHeight;
    }), 0.5);
    // And add it to the scene
    scene.addObject(MS_ptr);



    // For keeping track of the focus of the window
    bool hasFocus = true;
    while(window.isOpen()) {
        events.clear();
        for(Event ev; window.pollEvent(ev);) {
            events.push_back(ev);
            // Closes the window
            if(ev.type == Event::Closed)
                window.close();
            // Updates the view on resize (for scaling problems)
            if(ev.type == Event::Resized)
                updateWindowSize(window, view, Vector2f(ev.size.width, ev.size.height));

        }

        
        if(Keyboard::isKeyPressed(Keyboard::E)) MS_ptr.get()->m_funcHandler.setEqual(MS_ptr.get()->m_funcHandler.getEqual()-0.01);
        if(Keyboard::isKeyPressed(Keyboard::Q)) MS_ptr.get()->m_funcHandler.setEqual(MS_ptr.get()->m_funcHandler.getEqual()+0.01);
        


        // Don't update if the window isn't focused
        if(!window.hasFocus()) continue;

        // Update the camera movements
        controller.Update(window, events);

        // Update the window camera
        window.setView(view);

        // Clear the screen
        window.clear(Color(200, 215, 215));
        // Draw everything
        scene.draw(window);
        // And display it to the screen
        window.display();
    }
}