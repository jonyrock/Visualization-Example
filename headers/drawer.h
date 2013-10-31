#pragma once
#include "geom/primitives/segment.h"
#include "geom/primitives/vector.h"
#include "visualization/viewer.h"
#include "algorithms.h"

#include "math.h"

using namespace geom::structures;
using namespace visualization;

namespace drawer {
    
    using namespace geom::algorithms;
    
    void drawArrow(drawer_type& drawer, const segment_type& segment,
            double width = 1.0) {

        // base line
        drawer.draw_line(segment, width);

        vector_type vt = segment[0] - segment[1];

        double angle = atan2(vt.y * 1.0, vt.x * 1.0);

        int xe = segment[1].x;
        int ye = segment[1].y;

        for (float i = -0.5f; i <= 0.5; i += 0.1) {
            int xa = cos(angle + i) * 7 + xe;
            int ya = sin(angle + i) * 7 + ye;
            drawer.draw_line(segment_type(
                    point_type(xe, ye),
                    point_type(xa, ya)),
                    width);
        }

    }

    void drawPolygon(drawer_type& drawer, const std::vector<point_type>& polygon,
            double width = 1.0) {
        for (uint i = 0; i < polygon.size(); i++) {
            drawer::drawArrow(drawer, segment_type(
                    polygon[i],
                    polygon[(i + 1) % polygon.size()]),
                    width
                    );
        }
    }
    
    void drawTripVertex(drawer_type& drawer, const point_type& point, TRIP_TYPE type){
        cout << point << type << endl;
        point_type a(point);
        point_type b(point);
        a.x -= 5;
        b.x += 5;
        switch(type) {
            case TRIP_REGULAR:        
                drawer.set_color(Qt::green);
                cout << "reg";
                break;
            case TRIP_START:
                drawer.set_color(Qt::red);
                cout << "start";
                break;
            case TRIP_SPLIT:
                cout << "split";
                drawer.set_color(Qt::cyan);
                break;
            case TRIP_END:
                cout << "end";
                drawer.set_color(Qt::blue);
                break;
            case TRIP_MERGE:
                cout << "merge";
                drawer.set_color(Qt::darkGreen);
                break;
        }
        drawer.draw_line(segment_type(a, b), 10);
    }
    
}

