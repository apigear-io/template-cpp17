{{- /* Copyright (c) ApiGear UG 2020 */ -}}

{{- $interfaceName := Camel .Interface.Name  }}
{{- $class := printf "I%s" $interfaceName }}
{{- $sub_class := printf "%sSubscriber" $class }}
{{- $pub_class := printf "%sPublisher" $interfaceName }}

#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.publisher.h"
#include <algorithm>
{{ nl }}
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};

void {{$pub_class}}::subscribeToAllChanges({{$sub_class}}& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<{{$sub_class}}>(subscriber));
    }
}
{{- nl }}
void {{$pub_class}}::unsubscribeFromAllChanges({{$sub_class}}& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}
{{- nl }}
{{- range .Interface.Properties}}
{{- $property := . }}
{{- $camelProperty := Camel .Name }}
long {{$pub_class}}::subscribeTo{{$camelProperty}}Changed({{$interfaceName}}{{$camelProperty}}PropertyCb callback)
{
    return {{Camel $property.Name}}Publisher.subscribeForChange(callback);
}
{{- nl }}
void {{$pub_class}}::unsubscribeFrom{{$camelProperty}}Changed(long handleId)
{
    {{Camel $property.Name}}Publisher.unsubscribeFromChange(handleId);
}
{{- nl }}
void {{$pub_class}}::publish{{$camelProperty}}Changed({{cppParam "" $property}}) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().on{{$camelProperty}}Changed({{$property.Name}});
    }
    {{- /* TODO clean up subscriber if subscriber is not valid anymore */}}
    {{Camel $property.Name}}Publisher.publishChange({{$property.Name}});
}
{{- nl }}
{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
{{- $camelSignal := Camel .Name }}
long {{$pub_class}}::subscribeTo{{$camelSignal}}({{$interfaceName}}{{$camelSignal}}SignalCb callback)
{
    return {{Camel $signal.Name}}Publisher.subscribeForChange(callback);
}
{{- nl }}
void {{$pub_class}}::unsubscribeFrom{{$camelSignal}}(long handleId)
{
    {{Camel $signal.Name}}Publisher.unsubscribeFromChange(handleId);
}
{{- nl }}
void {{$pub_class}}::publish{{$camelSignal}}({{cppParams "" $signal.Params}}) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().on{{$camelSignal}}({{cppVars $signal.Params}});
    }
    {{- /* TODO clean up subscriber if subscriber is not valid anymore */}}
    {{Camel $signal.Name}}Publisher.publishChange({{cppVars $signal.Params}});
}
{{- nl }}
{{- end }}
