//
//  ProgressCardView.swift
//  DatasetProgress
//
//  Created by 彭世辰 on 2021/3/29.
//

import SwiftUI

struct ProgressCardView: View {
    var userName: String = "SB"
    @Binding var progress: String
    func delLastChar(sourceString: String) -> String {
        var s = sourceString
        s.removeLast()
        return s
    }
    var body: some View {
        VStack(alignment: .leading, spacing: 5) {
            Text(userName.uppercased() + ":")
                .font(.system(size: 60, weight: .bold, design: .rounded))
                .foregroundColor(.white)
                .shadow(color: Color(.displayP3, red: 63/255, green: 100/255, blue: 200/255, opacity: 1), radius: 5, x: -5, y: 5)
            Text(progress.hasSuffix("\n") ? delLastChar(sourceString: progress) : progress)
                .font(.system(size: 100, weight: .bold, design: .rounded))
                .foregroundColor(.white)
                .shadow(color: Color(.displayP3, red: 63/255, green: 100/255, blue: 200/255, opacity: 1), radius: 5, x: -5, y: 5)
        }
        .frame(width: 320, height: 280, alignment: .center)
        
        .background(LinearGradient(gradient: Gradient(colors: [Color(.displayP3, red: 73/255, green: 122/255, blue: 246/255, opacity: 1), Color(.displayP3, red: 92/255, green: 189/255, blue: 242/255, opacity: 1)]), startPoint: .bottomLeading, endPoint: .topTrailing))
        .cornerRadius(30)
        .shadow(color: Color(.systemGray), radius: 15, x: -5, y: 5)
        .padding()
        
    }
}

struct ProgressCardView_Previews: PreviewProvider {
    static var previews: some View {
        ProgressCardView(progress: .constant("644"))
    }
}
