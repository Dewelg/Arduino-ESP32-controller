package com.sever.sever;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.ip.tcp.TcpReceivingChannelAdapter;
import org.springframework.integration.ip.tcp.TcpSendingMessageHandler;
import org.springframework.integration.ip.tcp.connection.TcpNetServerConnectionFactory;
import org.springframework.integration.support.MessageBuilder;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageChannel;

import org.springframework.messaging.MessageHandler;

@SpringBootApplication
public class SeverApplication {

	@Bean
	public TcpNetServerConnectionFactory severConnection(){
		TcpNetServerConnectionFactory factory = new TcpNetServerConnectionFactory(5000);
		factory.setSingleUse(false);
		return factory;
	}

	@Bean
	public TcpReceivingChannelAdapter inbound(TcpNetServerConnectionFactory connectionFactory){
		TcpReceivingChannelAdapter adapter = new TcpReceivingChannelAdapter();
		adapter.setConnectionFactory(connectionFactory);
		adapter.setOutputChannelName("inputChannel");
		return adapter;
	}

	@Bean
    public MessageChannel inputChannel() {
        return new DirectChannel();
    }

	@Bean
	public MessageChannel outputChannel(){
		return new DirectChannel();
	}

	@Bean
	@ServiceActivator(inputChannel = "outputChannel")
	public TcpSendingMessageHandler outbound(TcpNetServerConnectionFactory connectionFactory){
		TcpSendingMessageHandler handler = new TcpSendingMessageHandler();
		handler.setConnectionFactory(connectionFactory);
		return handler;
	}
    
	@Bean
    @ServiceActivator(inputChannel = "inputChannel")
    public MessageHandler handleMessage() {
		return message -> {
			//Message from esp32
			String recieved = new String((byte[]) message.getPayload());
			System.out.println("Received: " + recieved);

			//repsone message 
			String response = "Message Recived";

			//retain connection made from message
			Object connectionID = message.getHeaders().get("ip_tcp_connectionId");

			//wrap payload in byte array and send to esp32
			if(connectionID != null){
				Message<byte[]> reply = MessageBuilder.withPayload(response.getBytes())
				.setHeader("ip_tcp_connectionId", connectionID)
				.build();

				outputChannel().send(reply);
			}
		
		};
		
		
    }

	public static void main(String[] args) {
		SpringApplication.run(SeverApplication.class, args);
	}

}
