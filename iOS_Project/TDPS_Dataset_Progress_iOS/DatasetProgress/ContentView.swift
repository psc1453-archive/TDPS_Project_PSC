//
//  ContentView.swift
//  DatasetProgress
//
//  Created by 彭世辰 on 2021/3/28.
//

import SwiftUI

struct ContentView: View {
    let users = ["psc", "wyx", "yyx", "lyx", "zxc", "wyh"]
    @State var progress: [String] = ["0", "0", "0", "0", "0", "0"]
    func refreshProgress() {
        for i in 0..<users.count {
            progress[i] = getUserProgress(userName: users[i])
        }
        progressAll = overallProgress()
    }
    @State var progressAll = ""
    func delLastChar(sourceString: String) -> String {
        var s = sourceString
        s.removeLast()
        return s
    }
    func overallProgress() -> String {
        var sum: Int = 0
        for userProgress in progress {
            sum = sum + (Int(delLastChar(sourceString: userProgress)) ?? 0)
        }
        return String(sum)
    }
    init() {
        UINavigationBar.appearance().largeTitleTextAttributes = [.foregroundColor: UIColor.init(displayP3Red: 55/255, green: 69/255, blue: 124/255, alpha: 1)]
    }
    var body: some View {
        NavigationView {
            VStack {
                ScrollView(.vertical) {
                    VStack {
                        ForEach(0..<users.count) { idx in
                            ProgressCardView(userName: users[idx], progress: $progress[idx])
                        }
                        ProgressCardView(userName: "total", progress: $progressAll)
                    }
                }
                Button(action: {
                    refreshProgress()
                }, label: {
                    Image(systemName: "arrow.clockwise.circle.fill")
                        .font(.largeTitle)
                })
            }
            .onAppear {
                refreshProgress()
            }
            .navigationTitle("Label Progress")
        }
        .edgesIgnoringSafeArea(.all)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
