#include "ofApp.h"

//-----------------------------------------------------------------------------------------
//


void ofApp::setup()
{
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	// Give us a starting point for the camera
	camera.setNearClip(0.01f);
	camera.setPosition( 0, 4, 10 );
	camera.setMovementMaxSpeed( 0.1f );
    
    //l1.setPointLight();
    mesh.clear();
    //l1.setup();
    y = 0; //ofSignedNoise(0, .5, 0);
    int mSz = 30;
    for (int x = 0; x < mSz-1; x++){
        for (int z =0; z< mSz-1; z++){
            ofPoint p = ofPoint(x-15, y, z-15);
            mesh.addVertex(p);
            mesh.addColor(ofFloatColor(0,255,0));
            
        }
    }
    //for (int i=0; i<mesh.getNumVertices(); i++){
    
//}
    for (int x=0; x<W-1; x++){
        for (int z =0; z<H-1; z++){
            int i1 = z + W * x;
            int i2 = z+1 + W * x;
            int i3 = z + W * (x+1);
            int i4 = z+1 + W * (x+1);
            mesh.addTriangle( i1, i3, i2 );
            mesh.addTriangle( i2, i3, i4 );
        }
    }
    
    int numV = mesh.getNumVertices();
    
    for (int i=0; i<numV-1; i++){
        //        for(int x=0; x<W; x++){
        //            for(int z=0; z<W; z++){
        ofPoint V = mesh.getVertex(i);
        float yNoise = ofSignedNoise(i*.8);
        V.y = yNoise*2;
        mesh.setVertex(i, V);
        color = ofColor(0, ofMap(yNoise, -1, 1, 0, 255), ofMap(yNoise, -1, 1, 0, 100), ofMap(yNoise, -1, 1, 255, 100));
        
        mesh.setColor(i, color);
    }

  //  }

    setNormals(mesh);
    //l1.enable();

	
}

//-----------------------------------------------------------------------------------------
//
void ofApp::update()
{
    //Get the elapsed time
//    float t = ofGetElapsedTimef();
//    int numV = mesh.getNumVertices();
////
//    for (int i=0; i<numV-1; i++){
////        for(int x=0; x<W; x++){
////            for(int z=0; z<W; z++){
////                int i = x +W *z;
//                ofPoint V = mesh.getVertex(i);
//                float yNoise = ofSignedNoise(.1, t*.5, .1);
//                V.y = yNoise;
//                mesh.setVertex(i, V);
//
//    
//   }

//    //make the vertices move
//    for (int z=0; z<H; z++) {
//        for (int x=0; x<W; x++) {
//            int i = x + W * y;       //Vertex index
//            ofPoint p = mesh.getVertex( i );
//            //Get Perlin noise value
//            float value =
//            ofNoise( x * 0.05, y * 0.05, time * 0.5 );
//            //Change z-coordinate of vertex
//            p.z = value * 100;
//            mesh.setVertex( i, p );
//            //Change color of vertex
//            mesh.setColor( i,
//                          ofColor( value*255, value * 255, 255 ) );
//        }
//    }
//    setNormals( mesh );  //Update the normals
    
//    ofPoint p = ofPoint (-1, 0, 0);
//    ofPoint p2 = ofPoint (0, 1, 0);
//    ofPoint p3= ofPoint (1, 0, 0);
//    mesh.addVertex(p);
//    mesh.addVertex(p2);
//    mesh.addVertex(p3);

}

//-----------------------------------------------------------------------------------------
//
void ofApp::draw()
{
	ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);	
	
	ofEnableDepthTest();
    //ofEnableLighting();
    l1.enable();
	
	camera.begin();
	
		// draw a grid on the floor
		ofSetColor( ofColor(60) );
		ofPushMatrix();
			ofRotate(90, 0, 0, -1);
			ofDrawGridPlane( 10 );
		ofPopMatrix();
 //    for( int i=0; i<mesh.getNumVertices(); i++){
//        for( int y = 0; y < mSz-1; y++ )
//        {
//            for( int x = 0; x < mSz-1; x++ )
//            {
//                int i1 = x + mSz * y;
//                int i2 = x+1 +mSz *y;
//                int i3 = x + mSz * (y+1);
//                int i4 = x+1 + mSz * (y+1);
//    
//                
//                mesh.addTriangle( i1, i2, i3 );
//                mesh.addTriangle( i2, i4, i3 );
//                
//            }
//        }

//    for( int z = 0; y < mSz-1; z++ ){
//        for( int x = 0; x < mSz-1; x++ ){
//            int pointIndex = i;
//            
//        
//            mesh.addIndex(pointIndex);
//            mesh.addTriangle( pointIndex, pointIndex + 1, pointIndex + 1 + mSz );
//            mesh.addTriangle( pointIndex, pointIndex + 1 + mSz, pointIndex + mSz );
//            
//        }
//    }
    
//        mesh.addIndex(i);
//        mesh.addTriangle(i-2, i-1, i);
       
//    }
    //setNormals(mesh);

    mesh.draw();
    
//    ofSetColor(ofColor::seaGreen);
//    ofCircle(0, 0, 10);
	
	camera.end();
    ofDisableLighting();
	ofSetColor( ofColor::white );
	ofDisableDepthTest();
    //mesh.clear();


	fontSmall.drawStringShadowed(ofToString(ofGetFrameRate(),2), ofGetWidth()-35, ofGetHeight() - 6, ofColor::whiteSmoke, ofColor::black );
}

//-----------------------------------------------------------------------------------------//
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}





void ofApp::keyPressed(int key)
{
	if( key == 'f' )
	{
		ofToggleFullscreen();
	}
}
