//
//  ContentView.swift
//  DatasetLabel
//
//  Created by 彭世辰 on 2021/3/26.
//

import SwiftUI
import URLImage

struct ContentView: View {
    @State private var position = CGSize.zero
    @GestureState private var dragOffset = CGSize.zero
    @State var location = CGPoint(x: 400, y: 400)
//    @State var location = CGPoint(x: 200, y: 200)
    @State var imageName: String = "0.png"
    @State var lastImageName: String = "0.png"
    let radius: CGFloat = 600.0
//    let radius: CGFloat = 250
//    let radius: CGFloat = 230
    let step = 16.0
    var simpleDrag: some Gesture {
        DragGesture()
            .onChanged { value in
                self.location = value.location
            }
    }
    @State var justOpen = true
    var body: some View {
        ZStack {
            URLImage(url: URL(string: "http://pscpeng.xyz:880/" + imageName)!) { image in
                image
                    .resizable()
                    .aspectRatio(contentMode: .fit)
            }
            VStack {
                HStack {
                    Button(action: {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " fuck " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }, label: {
                        Image(systemName: "person.fill.questionmark")
                            .font(.largeTitle)
                            .frame(height: 20, alignment: .center)
                            .padding()
                    })
                    
                    Button(action: {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: lastImageName + " redo " + CompileOption.user))
                        self.lastImageName = self.imageName
                    }, label: {
                        Image(systemName: "arrowshape.turn.up.backward")
                            .font(.largeTitle)
                            .frame(height: 20, alignment: .center)
                            .padding()
                    })
                }
                Spacer()
            }
            VStack(spacing: 30) {
                Degreer(step: step, radius: radius, imageName: $imageName, lastImageName: $lastImageName)
                    .frame(width: 2 * radius, height: radius)
                Circle()
                    .frame(width: 30, height: 30, alignment: .center)
                .gesture(
                            DragGesture()
                                .updating($dragOffset, body: { (value, state, transaction) in

                                    state = value.translation
                                })
                                .onEnded({ (value) in
                                    self.position.height += value.translation.height
                                    self.position.width += value.translation.width
                                })
                    )
            }
            .offset(x: position.width + dragOffset.width, y: position.height + dragOffset.height)
            .animation(.linear)
        }
        .edgesIgnoringSafeArea(.all)
        .onAppear {
            if justOpen {
                self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                self.justOpen = false
                print(self.justOpen)
            }
            
        }
        
        
        
            
            
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
