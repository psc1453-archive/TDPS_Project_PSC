//
//  TCP.swift
//  WOL
//
//  Created by 彭世辰 on 2020/10/3.
//

import Socket
import Foundation

func sendCommandToServer(host: String, port: Int, command: String) -> String {
    var dataToReturn: String = ""
    do {
//        var data = Data()
//        let addr = Socket.createAddress(for: "127.0.0.1", on: 12000)
//        let socket = try Socket.create(family: Socket.ProtocolFamily.inet, type: Socket.SocketType.datagram, proto: Socket.SocketProtocol.udp)
//        try socket.write(from: command, to: addr!)
//        try socket.readDatagram(into: &data)
//        print(String(data: data, encoding: .utf8))
        var data = Data()
        let socket = try Socket.create(family: Socket.ProtocolFamily.inet, type: Socket.SocketType.stream, proto: Socket.SocketProtocol.tcp)
        try socket.connect(to: host, port: Int32(port))
        try socket.write(from: command)
        try socket.read(into: &data)
        if let dataToPrint = String(data: data, encoding: .utf8) {
            print(dataToPrint)
            dataToReturn = dataToPrint
        }
        socket.close()
    } catch {
        print(error)
    }
    return dataToReturn
}
