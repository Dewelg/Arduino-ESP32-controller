package com.sever.sever;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.ip.tcp.TcpReceivingChannelAdapter;
import org.springframework.integration.ip.tcp.TcpSendingMessageHandler;
import org.springframework.integration.ip.tcp.connection.TcpNetServerConnectionFactory;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageChannel;

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
    
    @ServiceActivator(inputChannel = "inputChannel")
    public void handleMessage(Message<byte[]> message) {
        System.out.println("Received: " + new String(message.getPayload()));

		
    }

	public static void main(String[] args) {
		SpringApplication.run(SeverApplication.class, args);
	}

}
