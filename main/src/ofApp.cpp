#include "ofApp.h"

#include <iostream>
#include <vector>
#include "csg/csgjs.h"

using namespace std;

void addMeshModel(std::vector<ofMesh> & meshes, struct csgjs_model csgjs_model){

    // csgjs_model to csgjs_polygon
    std::vector<csgjs_polygon> poly_model = csgjs_modelToPolygons(csgjs_model);

    // 色の指定
    int colors[3];
    if (meshes.size() < 3) {
        switch(meshes.size()){
            case 0:
                colors[0] = 255;
                colors[1] = 0;
                colors[2] = 0;
                break;
            case 1:
                colors[0] = 0;
                colors[1] = 255;
                colors[2] = 0;
                break;
            case 2:
                colors[0] = 0;
                colors[1] = 0;
                colors[2] = 255;
                break;
        }

    } else {
        colors[0] = rand()&255;
        colors[1] = rand()&255;
        colors[2] = rand()&255;
    }

    ofMesh mesh;
    for (int i = 0; i<poly_model.size(); i++){
        for (int j=0; j<poly_model[i].vertices.size(); j++){
            mesh.addVertex(ofVec3f(poly_model[i].vertices[j].pos.x, poly_model[i].vertices[j].pos.y, poly_model[i].vertices[j].pos.z));
            mesh.addColor(ofColor(colors[0], colors[1], colors[2]));
        }
    }
    meshes.push_back(mesh);
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);

    int center1[3] = {0, 0, 0};
    int center2[3] = {2, 2, 2};

    // csgjs model
    struct csgjs_model cube1 = csgjs_cube(3, center1);
    struct csgjs_model cube2 = csgjs_cube(3, center2);

    // CSG処理
    struct csgjs_model intersection = csgjs_intersection(cube1, cube2);

    // 頂点座標をmesh配列追加
    addMeshModel(meshes, cube1);
    addMeshModel(meshes, cube2);
    addMeshModel(meshes, intersection);

    // カメラ位置
    // cam.setPosition(0, 0, 0);
    // cam.lookAt(ofVec3f(0, 0, 0));
    // cam.setTarget(ofVec3f(0, 0, 0));
    cam.setDistance(13.0f);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(64), ofColor(0));

    // ofSetColor(255);


    // cam.begin()とcam.end()で囲まれた範囲がマウスドラッグで視点変更可能
    cam.begin();

    // ofSetColor(ofColor::gray);
    for (int i=0; i<meshes.size(); i++){
        meshes[i].drawWireframe();
    }

    glPointSize(4);
    // ofSetColor(ofColor::white);
    for (int i=0; i<meshes.size(); i++){
        meshes[i].drawVertices();
    }

    cam.end();

    //////////////////////////////////////////////////////////
    // マウス上の頂点情報の表示
    //////////////////////////////////////////////////////////
    // int n = mesh.getNumVertices();
    // float nearestDistance = 0;
    // ofVec2f nearestVertex;
    // int nearestIndex = 0;
    // ofVec2f mouse(mouseX, mouseY);
    // for(int i = 0; i < n; i++) {
    //     ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
    //     float distance = cur.distance(mouse);
    //     if(i == 0 || distance < nearestDistance) {
    //         nearestDistance = distance;
    //         nearestVertex = cur;
    //         nearestIndex = i;
    //     }
    // }
    //
    // ofSetColor(ofColor::gray);
    // ofDrawLine(nearestVertex, mouse);
    //
    // ofNoFill();
    // ofSetColor(ofColor::yellow);
    // ofSetLineWidth(2);
    // ofDrawCircle(nearestVertex, 4);
    // ofSetLineWidth(1);
    //
    // ofVec2f offset(10, -10);
    // ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);
    //////////////////////////////////////////////////////////
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}
