//
//  Degreer.swift
//  DatasetLabel
//
//  Created by 彭世辰 on 2021/3/27.
//

import SwiftUI

struct Degreer: View {
    var step = 16.0
    var radius: CGFloat = 400.0
    let transparentColor = Color.init(.displayP3, red: 1, green: 1, blue: 1, opacity: 0.01)
    @Binding var imageName: String
    @Binding var lastImageName: String
    var body: some View {
        GeometryReader { geometry in
            let centerPoint = CGPoint(x: geometry.size.width / 2, y: geometry.size.height)
            ZStack {
                ZStack {
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: 0), endAngle: Angle(degrees: -(90 - 2.5 * step)), clockwise: true)
                        
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " R11 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 - 2.5 * step)), endAngle: Angle(degrees: -(90 - 1.5 * step)), clockwise: true)
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " R10 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 - 1.5 * step)), endAngle: Angle(degrees: -(90 - 0.5 * step)), clockwise: true)
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " R01 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 - 0.5 * step)), endAngle: Angle(degrees: -(90 + 0.5 * step)), clockwise: true)
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " 00 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 + 0.5 * step)), endAngle: Angle(degrees: -(90 + 1.5 * step)), clockwise: true)
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " L01 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 + 1.5 * step)), endAngle: Angle(degrees: -(90 + 2.5 * step)), clockwise: true)
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " L10 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 + 2.5 * step)), endAngle: Angle(degrees: -180), clockwise: true)
                    }
                    .fill(transparentColor)
                    .onTapGesture {
                        print(sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: imageName + " L11 " + CompileOption.user))
                        self.lastImageName = self.imageName
                        self.imageName = sendCommandToServer(host: "pscpeng.xyz", port: 1999, command: "0")
                    }
                }
                ZStack {
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: 0), endAngle: Angle(degrees: -(90 - 2.5 * step)), clockwise: true)
                        
                    }
                    .stroke(lineWidth: 5)
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 - 2.5 * step)), endAngle: Angle(degrees: -(90 - 1.5 * step)), clockwise: true)
                    }
                    .stroke(lineWidth: 5)
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 - 1.5 * step)), endAngle: Angle(degrees: -(90 - 0.5 * step)), clockwise: true)
                    }
                    .stroke(lineWidth: 5)
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 - 0.5 * step)), endAngle: Angle(degrees: -(90 + 0.5 * step)), clockwise: true)
                    }
                    .stroke(lineWidth: 5)
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 + 0.5 * step)), endAngle: Angle(degrees: -(90 + 1.5 * step)), clockwise: true)
                    }
                    .stroke(lineWidth: 5)
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 + 1.5 * step)), endAngle: Angle(degrees: -(90 + 2.5 * step)), clockwise: true)
                    }
                    .stroke(lineWidth: 5)
                    Path { path in
                        path.move(to: centerPoint)
                        path.addArc(center: centerPoint, radius: radius, startAngle: Angle(degrees: -(90 + 2.5 * step)), endAngle: Angle(degrees: -180), clockwise: true)
                        path.closeSubpath()
                        
                    }
                    .stroke(lineWidth: 5)
                }
                .foregroundColor(.red)
            }
        }
    }
}

struct Degreer_Previews: PreviewProvider {
    static var previews: some View {
        Degreer(imageName: .constant(""), lastImageName: .constant(""))
    }
}
